// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <print.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x12(
        KC_ESC , KC_Q,    KC_W,    KC_E,            KC_R,           KC_T, KC_DEL,  KC_F5,   KC_F2,   KC_Y,    KC_U,           KC_I,             KC_O,    KC_P,    KC_MINS,
        KC_TAB , KC_A,    KC_S,    KC_D,            KC_F,           KC_G,                            KC_H,    KC_J,           KC_K,             KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,            KC_V,           KC_B,                            KC_N,    KC_M,           KC_COMM,          KC_DOT,  KC_SLSH, KC_BSLS,
                 KC_LGUI, KC_LALT, LSFT_T(KC_LNG2), LT(2, KC_SPC),  MO(1),         KC_BTN1,          MO(1),   LT(2, KC_ENT),  RSFT_T(KC_LNG1),  KC_LBRC, KC_RBRC
               , KC_BTN3, G(KC_TAB), KC_BTN5, G(KC_D), KC_BTN4, KC_BTN3, G(KC_TAB), G(C(KC_RGHT)), G(KC_D), G(C(KC_LEFT))
    ),

    [1] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
        _______, _______, _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                            KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______,
                 _______, _______, _______, _______, _______,          _______,          _______, KC_BSPC, _______, _______, _______
               , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT_ortho_4x12(
        KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                            KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
        KC_F11 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                            KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F12 ,
                 _______, _______, _______, _______, _______,          KC_KB_MUTE,       _______, _______, _______, _______, _______
               , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_UP, KC_DOWN) },
    [1] =   { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [2] =   { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN) }
};
