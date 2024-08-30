/* Copyright 2024 Geek-rabb1t (@geek-rabb1t)
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
#include "wait.h"
#include "futaba_azoteq_iqs5xx_driver.h"

const static int THREE_FINGER_GESTURE_ROW = 9;
const static int FOUR_FINGER_GESTURE_ROW =  10;

void matrix_scan_kb(void) {

    if (trackpad_event.type != trackpad_event_none) {
        int row = trackpad_event.num_of_fingers == 3 ?
                    THREE_FINGER_GESTURE_ROW : FOUR_FINGER_GESTURE_ROW;
        action_exec(MAKE_KEYEVENT(row, trackpad_event.type, true));
        wait_ms(10);
        action_exec(MAKE_KEYEVENT(row, trackpad_event.type, false));
        reset_trackpad_event();
    }

    matrix_scan_user();
}

#define SCROLL_SCALE_PERCENT 5

int32_t scroll_amount_h = 0;
int32_t scroll_amount_v = 0;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    scroll_amount_h += mouse_report.h * SCROLL_SCALE_PERCENT;
    scroll_amount_v += mouse_report.v * SCROLL_SCALE_PERCENT;
    int8_t h = scroll_amount_h / 100;
    int8_t v = scroll_amount_v / 100;
    scroll_amount_h -= h*100;
    scroll_amount_v -= v*100;

    mouse_report.h = h;
    mouse_report.v = v;
    return mouse_report;
}
