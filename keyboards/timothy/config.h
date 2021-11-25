/*
Copyright 2021 geek-rabb1t

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER geek-rabb1t
#define PRODUCT      Timothy

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { C6, E6, D7, B3, B6 }
#define MATRIX_COL_PINS { F5, B1, F6, D4, B5, B4, D1 }
// #define MATRIX_COL_PINS { F5, B1, F6, D4, B5, B4, B2 }  // TEST for I2C
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6
#define SPLIT_HAND_PIN D0
// #define USE_I2C

//#define LED_NUM_LOCK_PIN B0
//#define LED_CAPS_LOCK_PIN B1
//#define LED_SCROLL_LOCK_PIN B2
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

//#define BACKLIGHT_PIN B7
//#define BACKLIGHT_LEVELS 3
//#define BACKLIGHT_BREATHING

#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
//*
// RGB Lighting
#    define RGBLED_NUM 82
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_SLEEP
//#    define RGBLIGHT_ANIMATIONS
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_TWINKLE


#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#    define RGBLIGHT_DEFAULT_HUE 64
#    define RGBLIGHT_LIMIT_VAL 64
#    define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
/*/
// RGB Matrix
#    define DRIVER_LED_TOTAL 68
#    define RGB_MATRIX_KEYPRESSES
#    define SPLIT_TRANSPORT_MIRROR

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 20 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP // Sets the default mode, if none has been set
#    define RGB_DISABLE_TIMEOUT 60000 // number of milliseconds to wait until rgb automatically turns off
//#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_STARTUP_HUE 0 // Sets the default hue value, if none has been set
#    define RGB_MATRIX_STARTUP_SAT 0 // Sets the default saturation value, if none has been set
// #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#    define RGB_MATRIX_STARTUP_SPD 127 // Sets the default animation speed, if none has been set
// #define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)
#define RGB_MATRIX_SPLIT { 34, 34 }     // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.
                                      // If RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR

#    define DISABLE_RGB_MATRIX_ALPHAS_MODS
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define DISABLE_RGB_MATRIX_BREATHING
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_VAL
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define DISABLE_RGB_MATRIX_CYCLE_ALL
#    define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define DISABLE_RGB_MATRIX_DUAL_BEACON
#    define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#    define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS

#    define DISABLE_RGB_MATRIX_RAINDROPS
#    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

#    define DISABLE_RGB_MATRIX_HUE_BREATHING
#    define DISABLE_RGB_MATRIX_HUE_PENDULUM
#    define DISABLE_RGB_MATRIX_HUE_WAVE

//#    define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define DISABLE_RGB_MATRIX_SPLASH
#    define DISABLE_RGB_MATRIX_MULTISPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
//#    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
//*/
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0


// #define WS2812_ADDRESS 0xb0 // default: 0xb0
// #define WS2812_TIMEOUT 100 // default: 100
