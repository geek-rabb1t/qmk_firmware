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

typedef struct {
    int x;
    int y;
    mouse_xy_report_t mouse_report_x;
    mouse_xy_report_t mouse_report_y;
    int touch_strength;
    int num_of_fingers;
} trackpad_base_data_t;


typedef enum {
    touch_state_none,
    touch_state_touch,
    touch_state_press,
} touch_state_t;

typedef enum {
    trackpad_state_idle,
    trackpad_state_touch,
    trackpad_state_move,
    trackpad_state_gesture,
    trackpad_state_gesture_fire,
    trackpad_state_press,
    trackpad_state_wait,
} trackpad_state_t;

typedef enum  {
    trackpad_event_none = -1,
    trackpad_event_tap = 0,
    trackpad_event_swipe_up = 1,
    trackpad_event_swipe_right = 2,
    trackpad_event_swipe_down = 3,
    trackpad_event_swipe_left = 4,
} trackpad_gesture_event_t;

typedef struct {
    trackpad_gesture_event_t type;
    int8_t num_of_fingers;
} trackpad_event_t;

extern trackpad_event_t trackpad_event;

const static int8_t FUTABA_SWIPE_THRESHOLD_PIXEL = 10;
const static uint16_t FUTABA_RETAP_WAITING_TIME = 200;
 // 必ずpressにする閾値
const static uint16_t FUTABA_TAP_STRENGTH_THRESHOLD = 850;
// 弱いタッチでもクリックにする時間の最大値
const static uint16_t FUTABA_MAX_TAP_TIME = 200;

#define SCROLL_SCALE_PERCENT 10

#define FUTABA_REVERSE_SCROLL_X false
#define FUTABA_REVERSE_SCROLL_Y true

void reset_trackpad_event(void);
