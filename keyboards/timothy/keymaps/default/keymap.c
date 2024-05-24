/* Copyright 2021 geek-rabb1t
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _L1,
    _L2,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CK_LSFT = SAFE_RANGE,
    CK_RSFT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base
   *                               ,------.                                  ,------.
   *                               |DF_ADJ|                                  | SLEEP|
   * ,--------------------------------------------------.      ,--------------------------------------------------.
   * |   `  |   1  |   2  |    3   |   4  |   5  |VD_PRV|      |VD_NXT|   6  |   7  |    8   |   9  |   0  |  -   |
   * |------+------+------+--------+------+------+------|      |------+------+------+--------+------+------+------|
   * |  ESC |   q  |   w  |    e   |   r  |   t  |  F5  |      |  F2  |   y  |   u  |    i   |   o  |   p  |  =   |
   * |------+------+------+--------+------+------+------|      |------+------+------+--------+------+------+------|
   * |  Tab |   a  |   s  |    d   |   f  |   g  |  INS |      |  F8  |   h  |   j  |    k   |   l  |   ;  |  '   |
   * |------+------+------+--------+------+------+------|      |------+------+------+--------+------+------+------|
   * | CTRL |   z  |   x  |    c   |   v  |   b  |  DEL |      |  F12 |   n  |   m  |    ,   |   .  |   /  |  \   |
   * |-------------+------+--------+------+------+------|      |------+------+------+--------+------+-------------|
   * ||||||||  GUI |  Alt |SFT/LNG2| Space|CURSOR||||||||      ||||||||CURSOR| Enter|SFT/LNG1|   [  |  ]   ||||||||
   * ,--------------------------------------------------.      ,--------------------------------------------------.
   */
  [_BASE] = LAYOUT(
                                                DF(_ADJUST) ,                                                   KC_SLEP ,
     KC_GRV    , KC_1   , KC_2  , KC_3          , KC_4    , KC_5   , G(C(KC_LEFT)),      G(C(KC_RGHT)) , KC_6   , KC_7    , KC_8          , KC_9   , KC_0  ,KC_MINS  , \
     KC_ESC    , KC_Q   , KC_W  , KC_E          , KC_R    , KC_T   , KC_F5        ,      KC_F2         , KC_Y   , KC_U    , KC_I          , KC_O   , KC_P  ,KC_EQL   , \
     KC_TAB    , KC_A   , KC_S  , KC_D          , KC_F    , KC_G   , KC_INS       ,      KC_F8         , KC_H   , KC_J    , KC_K          , KC_L   ,KC_SCLN,KC_QUOT  , \
     KC_LCTL   , KC_Z   , KC_X  , KC_C          , KC_V    , KC_B   , KC_DEL       ,      KC_F12        , KC_N   , KC_M    ,KC_COMM        , KC_DOT ,KC_SLSH,KC_BSLS  , \
                 KC_LGUI,KC_LALT,LSFT_T(KC_LNG2), KC_SPC , MO(_L1) ,                                   MO(_L1)  , KC_ENT  ,RSFT_T(KC_LNG1), KC_LBRC,KC_RBRC            \
  ),

  /* Cursor
   *                             ,------.                                  ,------.
   *                             |      |                                  |      |
   * ,------------------------------------------------.      ,------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  | Mute |      | PSCR |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * | SLEEP|      |      |      |      |      |      |      |      | Home | PgDw | PgUp |  End |      |      |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * |TSK_VW|      |      |      |      |      |      |      |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * | C+A+D|      |      |      |      |      |      |      |      |   {  |   }  |   [  |   ]  |      |      |
   * |-------------+------+------+------+------+------|      |------+------+------+------+------+-------------|
   * ||||||||      |      |      |      |      ||||||||      |||||||| BSPC |      |      |      |      ||||||||
   * ,------------------------------------------------.      ,------------------------------------------------.
   */
  [_L1] = LAYOUT(                           _______,                                             _______,
    KC_F11     , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5,   RCS(KC_M),       KC_PSCR, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 , \
    KC_SLEP    , _______, _______, _______, _______, _______, _______  ,       _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______, \
    G(KC_TAB)  , _______, _______, _______, _______, _______, _______  ,       _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, \
    LCA(KC_DEL), _______, _______, _______, _______, _______, _______  ,       _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______, \
                 _______, _______, _______, _______, _______,                           _______, KC_BSPC, _______, _______, _______           \
  ),

    /* Cursor
   *                             ,------.                                  ,------.
   *                             |      |                                  |      |
   * ,------------------------------------------------.      ,------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  | Mute |      | PSCR |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * | SLEEP|      |      |      |      |      |      |      |      | Home | PgDw | PgUp |  End |      |      |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * |TSK_VW|      |      |      |      |      |      |      |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
   * | C+A+D|      |      |      |      |      |      |      |      |   {  |   }  |   [  |   ]  |      |  LED |
   * |-------------+------+------+------+------+------|      |------+------+------+------+------+-------------|
   * ||||||||      |      |      |      |      ||||||||      |||||||| BSPC |      |      |      |      ||||||||
   * ,------------------------------------------------.      ,------------------------------------------------.
   */
  [_L2] = LAYOUT(
                                        XXXXXXX,                                           XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX           \
  ),

  /* Setting
   *                             ,-------.                                 ,------.
   *                             |DF_BASE|                                 |QK_RBT|
   * ,------------------------------------------------------.      ,-------------------------------------------------.
   * |      |      |       |       |       |        |RGB_TOG|      |EEP_RST|      |      |      |      |      |      |
   * |------+------+-------+-------+-------+--------+-------|      |-------+------+------+------+------+------+------|
   * |      |      |       |       |       |        |       |      |       |      |      |      |      |      |      |
   * |------+------+-------+-------+-------+--------+-------|      |-------+------+------+------+------+------+------|
   * |      |      |RGB_HUI|RGB_SAI|RGB_VAI|RGB_MOD |       |      |       |      |      |      |      |      |      |
   * |------+------+-------+-------+-------+--------+-------|      |-------+------+------+------+------+------+------|
   * |      |      |RGB_HUD|RGB_SAD|RGB_VAD|RGB_RMOD|       |      |       |      |      |      |      |      |      |
   * |-------------+-------+-------+-------+--------+-------|      |-------+------+------+------+------+-------------|
   * ||||||||      |      |      |      |      |    |||||||||      |||||||||      |      |      |      |      ||||||||
   * ,------------------------------------------------------.      ,-------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
                                       DF(_BASE),                                          QK_RBT ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,  XXXXXXX, RGB_TOG,       EE_CLR , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,  XXXXXXX, RGB_M_P,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI ,  RGB_MOD, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD , RGB_RMOD, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,  XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX           \
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    return true;
}


void keyboard_post_init_user(void) {
  // rgb lightの初期値を設定
//  rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, 255, RGBLIGHT_LIMIT_VAL);
}
/*
void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
}

void suspend_wakeup_init_user(void) {
    // code will run on keyboard wakeup
}
*/
// called by each layer changes

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {

    case _L1:
        rgb_matrix_sethsv_noeeprom((rgb_matrix_get_hue() + 21) % 255, rgb_matrix_get_sat(), rgb_matrix_get_val());
        break;
    case _L2:
        rgb_matrix_sethsv_noeeprom((rgb_matrix_get_hue() + 234) % 255, rgb_matrix_get_sat(), rgb_matrix_get_val());
        break;
    case _ADJUST:
        rgb_matrix_sethsv_noeeprom((rgb_matrix_get_hue() + 116) % 255, rgb_matrix_get_sat(), rgb_matrix_get_val());
        break;
    default: //  他の全てのレイヤーあるいはデフォルトのレイヤー
        rgb_matrix_reload_from_eeprom();
        break;
    }
  return state;
}


/*
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
}
*/
