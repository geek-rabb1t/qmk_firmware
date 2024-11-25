/* Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
 * Copyright 2024 Geek-rabb1t (@geek-rabb1t)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "i2c_master.h"
#include "azoteq_iqs5xx.h"
#include "pointing_device_internal.h"
#include "pointing_device.h"
#include "debug.h"
#include "wait.h"
#include "timer.h"
#include "gr_trackpad65_driver.h"
#include <math.h>

#define CONSTRAIN_HID(amt) ((amt) < INT8_MIN ? INT8_MIN : ((amt) > INT8_MAX ? INT8_MAX : (amt)))
#define CONSTRAIN_HID_XY(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))


static uint16_t cpi;



trackpad_event_t trackpad_event = {
    .type = trackpad_event_none,
    .num_of_fingers = 0
};

static i2c_status_t azoteq_iqs5xx_init_status = 1;

void pointing_device_driver_init(void) {
    i2c_init();
    azoteq_iqs5xx_wake();
    azoteq_iqs5xx_reset_suspend(true, false, true);
    wait_ms(100);
    azoteq_iqs5xx_wake();
    if (azoteq_iqs5xx_get_product() != AZOTEQ_IQS5XX_UNKNOWN) {
        azoteq_iqs5xx_setup_resolution();
        azoteq_iqs5xx_init_status = azoteq_iqs5xx_set_report_rate(AZOTEQ_IQS5XX_REPORT_RATE, AZOTEQ_IQS5XX_ACTIVE, false);
        azoteq_iqs5xx_init_status |= azoteq_iqs5xx_set_event_mode(false, false);
        azoteq_iqs5xx_init_status |= azoteq_iqs5xx_set_reati(true, false);
        azoteq_iqs5xx_init_status |= azoteq_iqs5xx_set_xy_config(false, false, false, true, false);
        azoteq_iqs5xx_init_status |= azoteq_iqs5xx_set_gesture_config(true);
        wait_ms(AZOTEQ_IQS5XX_REPORT_RATE + 1);
        cpi = azoteq_iqs5xx_get_cpi();
    }
};

void dispatch_swipe_gesture(int16_t swipe_distance_x, int16_t swipe_distance_y, int8_t num_of_fingers) {
    swipe_distance_x = abs(swipe_distance_x) >= FUTABA_SWIPE_THRESHOLD_PIXEL ? swipe_distance_x : 0;
    swipe_distance_y = abs(swipe_distance_y) >= FUTABA_SWIPE_THRESHOLD_PIXEL ? swipe_distance_y : 0;
    if (swipe_distance_x == 0 && swipe_distance_y == 0) {
        reset_trackpad_event();
        return;
    }

    trackpad_gesture_event_t event = abs(swipe_distance_x) > abs(swipe_distance_y) ?
            (swipe_distance_x > 0 ? trackpad_event_swipe_right : trackpad_event_swipe_left):
            (swipe_distance_y > 0 ? trackpad_event_swipe_down : trackpad_event_swipe_up);

    pd_dprintf("swipe - %d fingers, direction: %d, x:%d, y:%d.\n",num_of_fingers, event, swipe_distance_x, swipe_distance_y);

    trackpad_event.type = event;
    trackpad_event.num_of_fingers = num_of_fingers;
}

void dispatch_multi_tap(int8_t num_of_fingers) {

    pd_dprintf("tap - %d fingers.\n",num_of_fingers);

    trackpad_event.type = trackpad_event_tap;
    trackpad_event.num_of_fingers = num_of_fingers;
}

void reset_trackpad_event(void) {
    trackpad_event.type = trackpad_event_none;
    trackpad_event.num_of_fingers = 0;
}

int8_t calc_max_fingers(int8_t current, int8_t previous) {
    return (previous > current) ? previous :current;
}

static uint8_t max_fingers = 0;
static int16_t swipe_distance_x = 0;
static int16_t swipe_distance_y = 0;
static uint16_t tap_interval = 0;
static uint16_t tap_timer = 0;
static bool doubleTap = false;


static trackpad_state_t trackpad_state = trackpad_state_idle;

void reset_gesture_status(void) {
    if (max_fingers != 0) {
        pd_dprintf("reset state.\n");
    }

    max_fingers = 0;
    swipe_distance_x = 0;
    swipe_distance_y = 0;
    doubleTap = false;
}


report_mouse_t idle_strategy(trackpad_base_data_t trackpad_data) {
    reset_gesture_status();
    report_mouse_t report = {0};
    return report;
}

report_mouse_t touch_strategy(trackpad_base_data_t trackpad_data) {
    report_mouse_t temp_report = {0};
    return temp_report;
}

report_mouse_t move_strategy(trackpad_base_data_t trackpad_data) {
    // pd_dprintf("move: %d fingers.\n",trackpad_data.num_of_fingers);
    report_mouse_t temp_report = {0};
    if (trackpad_data.num_of_fingers  >= 2) {

        int scroll_dir_x = (FUTABA_REVERSE_SCROLL_X) ? -1 : 1;
        int scroll_dir_y = (FUTABA_REVERSE_SCROLL_Y) ? -1 : 1;

        int scroll_x = trackpad_data.x * SCROLL_SCALE_PERCENT / 100 * scroll_dir_x;
        int scroll_y = trackpad_data.y * SCROLL_SCALE_PERCENT / 100 * scroll_dir_y;

        temp_report.h = CONSTRAIN_HID(scroll_x);
        temp_report.v = CONSTRAIN_HID(scroll_y);


    } else {
        temp_report.x = trackpad_data.mouse_report_x;
        temp_report.y = trackpad_data.mouse_report_y;
    }

    return temp_report;
}

report_mouse_t gesture_strategy(trackpad_base_data_t trackpad_data) {
    report_mouse_t temp_report = {0};

    swipe_distance_x += trackpad_data.x;
    swipe_distance_y += trackpad_data.y;

    return temp_report;
}

report_mouse_t gesture_fire_strategy(trackpad_base_data_t trackpad_data) {
    report_mouse_t temp_report = {0};

    pd_dprintf("gesture: %d fingers.(%d, %d)\n",max_fingers, swipe_distance_x, swipe_distance_y);
    dispatch_swipe_gesture(swipe_distance_x, swipe_distance_y, max_fingers);

    return temp_report;
}

pointing_device_buttons_t dispatch_buttons(int num_of_fingers) {
    return
        (num_of_fingers == 3) ?     POINTING_DEVICE_BUTTON3 :
        ((num_of_fingers == 2) ?    POINTING_DEVICE_BUTTON2 :
                                    POINTING_DEVICE_BUTTON1);
}

report_mouse_t press_strategy(trackpad_base_data_t trackpad_data) {
    report_mouse_t temp_report = {0};

    pointing_device_buttons_t button = dispatch_buttons(max_fingers);
    // pd_dprintf("press: %d fingers.\n",max_fingers);
    temp_report.buttons = pointing_device_handle_buttons(temp_report.buttons, true, button);

    if (trackpad_data.mouse_report_x != 0 || trackpad_data.mouse_report_y != 0) {
        doubleTap = false;
    }

    temp_report.x = trackpad_data.mouse_report_x;
    temp_report.y = trackpad_data.mouse_report_y;

    return temp_report;
}

report_mouse_t wait_strategy(trackpad_base_data_t trackpad_data) {
    report_mouse_t temp_report = {0};

    if (doubleTap) {
        doubleTap = false;
        return temp_report;
    }
    pointing_device_buttons_t button = dispatch_buttons(max_fingers);
    // pd_dprintf("press wait: %d fingers.\n",max_fingers);
    temp_report.buttons = pointing_device_handle_buttons(temp_report.buttons, true, button);

    return temp_report;
}

report_mouse_t (*find_strategy(trackpad_state_t state))(trackpad_base_data_t) {
    switch (state) {
        case trackpad_state_idle: return idle_strategy;
        case trackpad_state_touch: return touch_strategy;
        case trackpad_state_move: return move_strategy;
        case trackpad_state_gesture: return gesture_strategy;
        case trackpad_state_gesture_fire: return gesture_fire_strategy;
        case trackpad_state_press: return press_strategy;
        case trackpad_state_wait: return wait_strategy;
    }
    return idle_strategy;
}


touch_state_t get_touch_state(trackpad_base_data_t trackpad_data) {
    if (trackpad_data.touch_strength == 0) {
        return touch_state_none;
    } else if (trackpad_data.touch_strength >= FUTABA_TAP_STRENGTH_THRESHOLD) {
        return touch_state_press;
    }
    return touch_state_touch;

}

trackpad_state_t update_current_state(trackpad_base_data_t trackpad_data, trackpad_state_t prev_state) {
    touch_state_t touch_state = get_touch_state(trackpad_data);
    // pd_dprintf("touch: %d.\n",touch_state);

    // The state of the trackpad is determined by a combination of the previous state and the current touch state.
    if (prev_state == trackpad_state_idle) {
        if (touch_state == touch_state_touch) {
            tap_timer = timer_read();
            max_fingers = calc_max_fingers(trackpad_data.num_of_fingers, max_fingers);
            return trackpad_state_touch;
        }
        if (touch_state == touch_state_press) {
            max_fingers = calc_max_fingers(trackpad_data.num_of_fingers, max_fingers);
            return trackpad_state_press;
        }
    }

    if (prev_state == trackpad_state_touch) {
        max_fingers = calc_max_fingers(trackpad_data.num_of_fingers, max_fingers);
        if (touch_state == touch_state_none) {
            if (timer_elapsed(tap_timer) <= FUTABA_MAX_TAP_TIME) {
                return trackpad_state_press;
            }
            return trackpad_state_idle;
        }

        if (trackpad_data.mouse_report_x != 0 || trackpad_data.mouse_report_y != 0) {
            if (max_fingers > 2) {
                return trackpad_state_gesture;
            }
            return trackpad_state_move;
        }

        if (touch_state == touch_state_press) {
            if (timer_elapsed(tap_timer) <= FUTABA_MAX_TAP_TIME) {
                pd_dprintf("touch to press!!:%d, timer:%d\n", trackpad_data.touch_strength, timer_elapsed(tap_timer));
                return trackpad_state_press;
            }
        }
    }

    if (prev_state == trackpad_state_move) {
        if (touch_state == touch_state_none) {
            return trackpad_state_idle;
        }
    }

    if (prev_state == trackpad_state_gesture) {
        if (touch_state == touch_state_none) {
            return trackpad_state_gesture_fire;
        }
    }

    if (prev_state == trackpad_state_gesture_fire) {
        if (touch_state == touch_state_none) {
            return trackpad_state_idle;
        }
        if (touch_state == touch_state_touch) {
            return trackpad_state_touch;
        }
        if (touch_state == touch_state_press) {
            max_fingers = calc_max_fingers(trackpad_data.num_of_fingers, max_fingers);
            return trackpad_state_press;
        }
    }

    if(prev_state == trackpad_state_press) {
        if (touch_state == touch_state_none) {
            tap_interval = timer_read();
            return trackpad_state_wait;
        }
    }

    if (prev_state == trackpad_state_wait) {
        if (touch_state == touch_state_none) {
            if (timer_elapsed(tap_interval) >= FUTABA_RETAP_WAITING_TIME) {
                return trackpad_state_idle;
            }
        }

        if (touch_state == touch_state_touch || touch_state == touch_state_press) {
            doubleTap = true;
            return trackpad_state_press;
        }
    }

    return prev_state;
}

int get_touch_strength(azoteq_iqs5xx_base_data_t base_data) {
    int fingers[5] = {
        AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_1.touch_strength.h, base_data.finger_1.touch_strength.l),
        AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_2.touch_strength.h, base_data.finger_2.touch_strength.l),
        AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_3.touch_strength.h, base_data.finger_3.touch_strength.l),
        AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_4.touch_strength.h, base_data.finger_4.touch_strength.l),
        AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_5.touch_strength.h, base_data.finger_5.touch_strength.l)
    };
    int max = 0;
    for (int i = 0; i < base_data.number_of_fingers; i++) {
        if (fingers[i] > max) {
            max = fingers[i];
        }
    }
    return max;
}

typedef struct {
    int x;
    int y;
} position_t;

static position_t prev_positions[5] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
static int cursor_finger_num = 0;
static uint16_t timer;
// 指が 0本から 1本以上に変わった場合、一定サイクルは座標の変更を無視したほうがよさそう。
void get_finger_delta(azoteq_iqs5xx_base_data_t base_data, position_t *delta) {
    position_t fingers[5] = {
        {
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_1.absolute_x.h, base_data.finger_1.absolute_x.l),
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_1.absolute_y.h, base_data.finger_1.absolute_y.l),
        },
        {
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_2.absolute_x.h, base_data.finger_2.absolute_x.l),
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_2.absolute_y.h, base_data.finger_2.absolute_y.l),
        },
        {
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_3.absolute_x.h, base_data.finger_3.absolute_x.l),
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_3.absolute_y.h, base_data.finger_3.absolute_y.l),
        },
        {
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_4.absolute_x.h, base_data.finger_4.absolute_x.l),
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_4.absolute_y.h, base_data.finger_4.absolute_y.l),
        },
        {
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_5.absolute_x.h, base_data.finger_5.absolute_x.l),
            AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.finger_5.absolute_y.h, base_data.finger_5.absolute_y.l),
        },
    };

    position_t deltas[5] = {0};
    for (int i = 0; i < 5; i++) {
        if (i >= base_data.number_of_fingers) {
            fingers[i].x = -1;
            fingers[i].y = -1;
            prev_positions[i].x = -1;
            prev_positions[i].y = -1;
            continue;
        }

        if (i == 0 && prev_positions[i].x == -1) {
            timer = timer_read();
        }

        if (prev_positions[i].x != -1) {
            // カーソル飛び対策として、最大移動量を抑制
            int x = fingers[i].x - prev_positions[i].x;
            x = x > 300 ? 300 : x < -300 ? -300 : x;
            deltas[i].x = x;

            int y = fingers[i].y - prev_positions[i].y;
            y = y > 300 ? 300 : y < -300 ? -300 : y;
            deltas[i].y = y;
        }

        prev_positions[i].x = fingers[i].x;
        prev_positions[i].y = fingers[i].y;
    }

    if (timer_elapsed(timer) < 100) {
        delta->x = 0;
        delta->y = 0;
        return;
    }

    if (abs(deltas[cursor_finger_num].x) + abs(deltas[cursor_finger_num].y) > 2) {
        delta->x = deltas[cursor_finger_num].x;
        delta->y = deltas[cursor_finger_num].y;
        return;
    }

    for (int i = 0; i < base_data.number_of_fingers; i++) {
        if (abs(deltas[i].x) + abs(deltas[i].y) > 2) {
            delta->x = deltas[i].x;
            delta->x = deltas[i].y;
            cursor_finger_num = i;
            return;
        }
    }

    delta->x = 0;
    delta->y = 0;
    cursor_finger_num = 0;

    return;
}

mouse_xy_report_t correct_cursor(int delta, int prev, bool print) {

    int avg = (delta + prev);
    // 0.5 - 2倍 の間で可変
    int ratio = (fmin(abs(avg), 255)) * 15 / 255 + 5;
    int mov = avg * ratio / 20;

    return (mouse_xy_report_t) CONSTRAIN_HID_XY((int)mov);
}

static int prev_x = 0;
static int prev_y = 0;

report_mouse_t pointing_device_generate_report(azoteq_iqs5xx_base_data_t base_data) {

    position_t position = {0};
    get_finger_delta(base_data, &position);

    int x = AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.x.h, base_data.x.l);
    int y = AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.y.h, base_data.y.l);

    if (position.x != x || position.y != y || position.x >= 200) {
        pd_dprintf("cursor - delta: (%d, %d), relative: (%d, %d) \n", position.x, position.y, x, y);
    }


    trackpad_base_data_t trackpad_data = {
        .x              = position.x,
        .y              = position.y,
        .mouse_report_x = correct_cursor(position.x, prev_x, true),
        .mouse_report_y = correct_cursor(position.y, prev_y, false),
        .touch_strength = get_touch_strength(base_data),
        .num_of_fingers = base_data.number_of_fingers,
    };

    prev_x = position.x;
    prev_y = position.y;

    trackpad_state = update_current_state(trackpad_data, trackpad_state);
    // pd_dprintf("state: %d.\n",trackpad_state);
    return find_strategy(trackpad_state)(trackpad_data);
}


report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    report_mouse_t temp_report           = {0};
    static uint8_t previous_button_state = 0;
    static uint8_t read_error_count      = 0;

    if (azoteq_iqs5xx_init_status == I2C_STATUS_SUCCESS) {
        azoteq_iqs5xx_base_data_t base_data = {0};
        i2c_status_t status = azoteq_iqs5xx_get_base_data(&base_data);

        if (status == I2C_STATUS_SUCCESS) {
            read_error_count = 0;
            temp_report = pointing_device_generate_report(base_data);
            previous_button_state = temp_report.buttons;

        } else {
            if (read_error_count > 10) {
                read_error_count      = 0;
                previous_button_state = 0;
            } else {
                read_error_count++;
            }
            temp_report.buttons = previous_button_state;
            // pd_dprintf("IQS5XX - get report failed: %d \n", status);
        }
    } else {
        pd_dprintf("IQS5XX - Init failed: %d \n", azoteq_iqs5xx_init_status);
        azoteq_iqs5xx_get_product();
    }

    return temp_report;
}

uint16_t pointing_device_driver_get_cpi(void) {
    return azoteq_iqs5xx_get_cpi();
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    azoteq_iqs5xx_set_cpi(cpi);
}
