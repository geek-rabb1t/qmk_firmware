#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────────────┐
     * │    sleep   │
     * ├────────────┤
     * │ win+shft+a │
     * └────────────┘
     */
    [0] = LAYOUT_kvm(
        KC_SLEP,   G(S(KC_A))
    )
    //     [0] = LAYOUT_kvm(
    //     KC_A,   KC_B
    // )
};
