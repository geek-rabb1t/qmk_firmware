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
#include "drivers/sensors/azoteq_iqs5xx.h"
#include "pointing_device_internal.h"
#include "pointing_device.h"
#include "debug.h"
#include "wait.h"
#include "timer.h"
#include <stddef.h>
#include "futaba_azoteq_iqs5xx_driver.h"

#define CONSTRAIN_HID(amt) ((amt) < INT8_MIN ? INT8_MIN : ((amt) > INT8_MAX ? INT8_MAX : (amt)))
#define CONSTRAIN_HID_XY(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))


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
    }
};

void dispatch_swipe_gesture(int16_t swipe_distance_x, int16_t swipe_distance_y, int8_t num_of_fingers) {
    swipe_distance_x = abs(swipe_distance_x) >= FUTABA_SWIPE_THREADSHOLD_PIXEL ? swipe_distance_x : 0;
    swipe_distance_y = abs(swipe_distance_y) >= FUTABA_SWIPE_THREADSHOLD_PIXEL ? swipe_distance_y : 0;
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
    if (current == 0) {
        return 0;
    }

    return (previous > current) ? previous :current;
}

static uint8_t max_fingers = 0;
static gesture_mode_t gesture_mode = gesture_mode_none;
static int16_t swipe_distance_x = 0;
static int16_t swipe_distance_y = 0;
static int16_t tap_duration = 0;

void reset_gesture_status(void) {
    max_fingers = 0;
    gesture_mode = gesture_mode_none;
    swipe_distance_x = 0;
    swipe_distance_y = 0;
    tap_duration = 0;
}

report_mouse_t pointing_device_generate_report(azoteq_iqs5xx_base_data_t base_data) {
    report_mouse_t temp_report = {0};

    int x = CONSTRAIN_HID(AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.x.h, base_data.x.l));
    int y = CONSTRAIN_HID(AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.y.h, base_data.y.l));


    // end gesture
    if (base_data.number_of_fingers == 0) {

        if (gesture_mode == gesture_mode_swipe) {
            if (max_fingers >= 3) {
                dispatch_swipe_gesture(swipe_distance_x, swipe_distance_y, max_fingers);
            }
            reset_gesture_status();
        }

        if (gesture_mode == gesture_mode_tap) {
            if (tap_duration <= FUTABA_MAX_TAP_DURATION) {
                if (max_fingers >= 3) {
                    dispatch_multi_tap(max_fingers);
                } else if (max_fingers == 2) {
                    temp_report.buttons = pointing_device_handle_buttons(temp_report.buttons, true, POINTING_DEVICE_BUTTON2);
                }
            }
            reset_gesture_status();
        }
    }

    max_fingers = calc_max_fingers(base_data.number_of_fingers, max_fingers);

    if (max_fingers > 0) {
        // start gesture
        if (gesture_mode == gesture_mode_none) {
            reset_gesture_status();
            if (x == 0 && y == 0) {
                tap_duration = 0;
                gesture_mode = gesture_mode_tap;
            } else {
                gesture_mode = gesture_mode_swipe;
            }

        } else {

            // in gesture
            if (gesture_mode == gesture_mode_tap) {
                if (x == 0 && y == 0) {
                    tap_duration += base_data.previous_cycle_time;
                } else {
                    gesture_mode = gesture_mode_swipe;
                }
            }

            if (gesture_mode == gesture_mode_swipe) {
                if (max_fingers > 2) {
                    swipe_distance_x += x;
                    swipe_distance_y += y;

                // scroll
                } else if (max_fingers  == 2) {
                    #ifdef FUTABA_REVERSE_SCROLL_X
                        temp_report.h = x * -1;
                    #else
                        temp_report.h = x;
                    #endif
                    #ifdef FUTABA_REVERSE_SCROLL_Y
                        temp_report.v = y * -1;
                    #else
                        temp_report.v = y;
                    #endif
                } else {
                    temp_report.x = CONSTRAIN_HID_XY(AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.x.h, base_data.x.l));
                    temp_report.y = CONSTRAIN_HID_XY(AZOTEQ_IQS5XX_COMBINE_H_L_BYTES(base_data.y.h, base_data.y.l));
                }
            }
        }
    }

    if (base_data.gesture_events_0.single_tap || base_data.gesture_events_0.press_and_hold) {
        pd_dprintf("IQS5XX - Single tap/hold.\n");
        temp_report.buttons = pointing_device_handle_buttons(temp_report.buttons, true, POINTING_DEVICE_BUTTON1);
    }

    return temp_report;
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
            pd_dprintf("IQS5XX - get report failed: %d \n", status);
        }
    } else {
        pd_dprintf("IQS5XX - Init failed: %d \n", azoteq_iqs5xx_init_status);
    }

    return temp_report;
}

uint16_t pointing_device_driver_get_cpi(void) {
    return azoteq_iqs5xx_get_cpi();
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    azoteq_iqs5xx_set_cpi(cpi);
}
