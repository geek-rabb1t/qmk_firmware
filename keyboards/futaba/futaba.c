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

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    return pointing_device_task_user(mouse_report);
}
