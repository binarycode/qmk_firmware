/*
Copyright 2019 Igor Sidorov <igor.sidorov@binarycode.ru> @binarycode

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

#include QMK_KEYBOARD_H
#include "config.h"
#include "version.h"
#include "mousekey.h"

enum layers {
  BASE,
  NUMPAD,
  FUNCTION,
  MACRO,
  MOUSE
};

enum custom_keycodes {
    XX_NOP = SAFE_RANGE,
    // Diagonal mouse keys
    XX_M_NE,
    XX_M_NW,
    XX_M_SE,
    XX_M_SW,
    // Layer modifiers
    XX_L_NM,
    XX_L_FN,
    XX_L_MS,
    // Locking
    XX_LOCK,
    // Mouse selection lock
    XX_M_LK,
    // Firmware info
    XX_INFO,
    // Application switching
    XX_SW_L,
    XX_SW_G,
};

// Merge copy-paste with modifiers
#define XX_LCTL LCTL_T(KC_COPY)
#define XX_RCTL RCTL_T(KC_COPY)
#define XX_LALT LALT_T(KC_PASTE)
#define XX_RALT RALT_T(KC_PASTE)

// For consistency with diagonal mouse keys
#define XX_M_N KC_MS_UP
#define XX_M_S KC_MS_DOWN
#define XX_M_W KC_MS_LEFT
#define XX_M_E KC_MS_RIGHT

// Toggle MOUSE layout
#define XX_L_MS TG(MOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE LAYER
 * KC_QUOT (') is swapped in place of KC_SLSH (/)
 * HOLD LCTRL for LCTRL, TAP LCTRL for COPY
 * HOLD RCTRL for RCTRL, TAP RCTRL for COPY
 * HOLD LALT for LALT, TAP LALT for PASTE
 * HOLD RALT for RALT, TAP RALT for PASTE
 * HOLD FN for FUNCTION layer, TAP FN for TAB
 * HOLD NUM for NUMPAD layer, TAP NUM for KC_UNDR (_)
 * HOLD LOCK for key lock (works only for FN and NUM)
 * .--------------------------------------------. .--------------------------------------------.
 * | Q      | W      | E      | R      | T      | | Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | A      | S      | D      | F      | G      | | H      | J      | K      | L      | ;      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | Z      | X      | C      | V      | B      | | N      | M      | ,      | .      | '      |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          | LGUI   | LCTRL  | ESC    | FN     | | NUM    | BACKSP | RCTRL  | RGUI   |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          | LOCK   | LALT   | SPACE  | LSHIFT | | RSHIFT | ENTER  | RALT   | LOCK   |
 *          '-----------------------------------' '-----------------------------------'
 */
[BASE] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT,
             KC_LGUI, XX_LCTL, KC_ESC,  XX_L_FN,   XX_L_NM, KC_BSPC, XX_RCTL, KC_RGUI,
             XX_LOCK, XX_LALT, KC_SPC,  KC_LSPO,   KC_RSPC, KC_ENT,  XX_RALT, XX_LOCK
),

/* NUMPAD LAYER
 * .--------------------------------------------. .--------------------------------------------.
 * | `      | 7      | 8      | 9      | -      | |        |        |        |        |        |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | 4      | 5      | 6      | +      | |        |        |        |        |        |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | 1      | 2      | 3      | =      | |        |        |        |        |        |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        | 0      |        |        | |        |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[NUMPAD] = LAYOUT(
    KC_GRV,  KC_7,    KC_8,    KC_9,    KC_MINS,   _______, _______, _______, _______, _______,
    XXXXXXX, KC_4,    KC_5,    KC_6,    KC_PLUS,   _______, _______, _______, _______, _______,
    XXXXXXX, KC_1,    KC_2,    KC_3,    KC_EQL,    _______, _______, _______, _______, _______,
             _______, KC_0,    _______, _______,   _______, _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

/* FUNCTION LAYER
 * contains keys that did not fit on BASE layer ([, ], \, ', /)
 * .--------------------------------------------. .--------------------------------------------.
 * |        |        |        |        |        | | XXXXXX | XXXXXX | [      | ]      | \      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * |        |        |        |        |        | | LEFT   | DOWN   | UP     | RIGHT  | '      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * |        |        |        |        |        | | XXXXXX | XXXXXX | XXXXXX | XXXXXX | /      |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        |        | |        |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[FUNCTION] = LAYOUT(
    _______, _______, _______, _______, _______,   XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    _______, _______, _______, _______, _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLSH,
             _______, _______, _______, _______,   _______, _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

/* MACRO LAYER
 * TAP MOUSE to enter MOUSE layer
 * TAP INFO to get firmware information
 * TAP SWT_LO to switch between apps in the same workspace (ALT+ESC)
 * TAP SWT_GL to switch between apps (ALT+TAB)
 * .--------------------------------------------. .--------------------------------------------.
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | | MOUSE  | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | SWT_LO | XXXXXX | | XXXXXX | SWT_GL | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | | XXXXXX | XXXXXX | XXXXXX | XXXXXX | INFO   |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        |        | |        |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[MACRO] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XX_L_MS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XX_SW_L, XXXXXXX,   XXXXXXX, XX_SW_G, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XX_INFO,
             _______, _______, _______, _______,   _______, _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

/* MOUSE LAYER
 * TAP M_NW for KC_MS_UP + KC_MS_LEFT
 * TAP M_NE for KC_MS_UP + KC_MS_RIGHT
 * TAP M_SW for KC_MS_DOWN + KC_MS_LEFT
 * TAP M_SE for KC_MS_DOWN + KC_MS_RIGHT
 * TAP MOUSE to leave layer
 * .--------------------------------------------. .--------------------------------------------.
 * | XXXXXX | XXXXXX | XXXXXX | BTN2   | XXXXXX | | XXXXXX | M_NW   | M_N    | M_NE   | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | SLOW   | FAST   | BTN1   | XXXXXX | | XXXXXX | M_W    | M_LOCK | M_E    | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | BTN3   | XXXXXX | | XXXXXX | M_SW   | M_S    | M_SE   | XXXXXX |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        | MOUSE  | | MOUSE  |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[MOUSE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, XXXXXXX,   XXXXXXX, XX_M_NW, XX_M_N,  XX_M_NE, XXXXXXX,
    XXXXXXX, KC_ACL0, KC_ACL2, KC_BTN1, XXXXXXX,   XXXXXXX, XX_M_W,  XX_M_LK, XX_M_E,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX,   XXXXXXX, XX_M_SW, XX_M_S,  XX_M_SE, XXXXXXX,
             _______, _______, _______, XX_L_MS,   XX_L_MS, _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

};

bool mousekey_diagonal(bool pressed, uint16_t key1, uint16_t key2) {
    if (pressed) {
        mousekey_on(key1);
        mousekey_on(key2);
    } else {
        mousekey_off(key1);
        mousekey_off(key2);
    }
    mousekey_send();
    return false;
}

bool toggle_mouse_lock(bool pressed) {
    static bool mouse_lock = false;
    mouse_lock = pressed;
    if (mouse_lock) {
        mousekey_on(KC_BTN1);
    } else {
        mousekey_off(KC_BTN1);
    }
    return false;
}

inline bool app_switch_local(bool pressed) {
    if (pressed) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_ESCAPE) SS_UP(X_LALT));
    }
    return false;
}

inline bool app_switch_global(bool pressed) {
    if (pressed) {
        SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
    }
    return false;
}

inline bool firmware_info(bool pressed) {
    if (pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
}

bool switch_layer(bool pressed, int layer, bool lock, bool* interrupted, const char* str) {
    static uint16_t timer = 0;
    if (pressed) {
        timer = timer_read();
        *interrupted = false;
        layer_on(layer);
    } else if (!lock) {
        if (!*interrupted && (timer_elapsed(timer) < TAPPING_TERM)) {
            send_string_P(str);
        }
        layer_off(layer);
    }
    return false;
}

uint32_t layer_state_set_user(uint32_t state) {
    toggle_mouse_lock(false);

    state = update_tri_layer_state(state, NUMPAD, FUNCTION, MACRO);

    switch (biton32(state)) {
        case BASE:
            set_led_off;
            break;
        case NUMPAD:
            set_led_blue;
            break;
        case FUNCTION:
            set_led_red;
            break;
        case MACRO:
            set_led_magenta;
            break;
        case MOUSE:
            set_led_green;
            break;
        default:
            set_led_white;
            break;
    }

    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool pressed = record->event.pressed;

    static bool lock        = false;
    static bool interrupted = false;

    if (pressed) interrupted = true;

    switch (keycode) {
        case XX_M_NE:
            return mousekey_diagonal(pressed, KC_MS_UP, KC_MS_RIGHT);

        case XX_M_NW:
            return mousekey_diagonal(pressed, KC_MS_UP, KC_MS_LEFT);

        case XX_M_SE:
            return mousekey_diagonal(pressed, KC_MS_DOWN, KC_MS_RIGHT);

        case XX_M_SW:
            return mousekey_diagonal(pressed, KC_MS_DOWN, KC_MS_LEFT);

        case XX_LOCK:
            lock = pressed;
            return false;

        case XX_L_NM:
            return switch_layer(pressed, NUMPAD, lock, &interrupted, PSTR("_"));

        case XX_L_FN:
            return switch_layer(pressed, FUNCTION, lock, &interrupted, PSTR(SS_TAP(X_TAB)));

        case XX_M_LK:
            return toggle_mouse_lock(pressed);

        case XX_INFO:
            return firmware_info(pressed);

        case XX_SW_L:
            return app_switch_local(pressed);

        case XX_SW_G:
            return app_switch_global(pressed);
    }
    return true;
}

void keyboard_post_init_user() {
    set_led_off;
}
