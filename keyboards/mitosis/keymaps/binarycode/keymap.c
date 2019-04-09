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

#define ALT_ESC_TIMEOUT 380
#define GUI_TAB_TIMEOUT 380

// Layers
enum {
  BASE,
  NUMPAD,
  FUNCTION,
  MACRO,
  MOUSE
};

// Custom keycodes
enum {
    _NOP = SAFE_RANGE,
    // Diagonal mouse keys
    _MS_NE,
    _MS_NW,
    _MS_SE,
    _MS_SW,
    // Mouse selection lock
    _MS_LK,
    // Extended MO(layer)
    _MO_NM,
    _MO_FN,
    // Firmware info
    _INFO,
};

// Tap dances
enum {
    TD_ALTESC,
    TD_GUITAB
};

// For consistency with diagonal mouse keys
#define _MS_N KC_MS_UP
#define _MS_S KC_MS_DOWN
#define _MS_W KC_MS_LEFT
#define _MS_E KC_MS_RIGHT

// Toggle layout
#define _TG_NM TG(NUMPAD)
#define _TG_FN TG(FUNCTION)
#define _TG_MS TG(MOUSE)

// Tap dance
#define _ALTESC TD(TD_ALTESC)
#define _GUITAB TD(TD_GUITAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE LAYER
 * HOLD MO(FN) for FUNCTION layer, TAP MO(FN) for KC_TAB
 * HOLD MO(NM) for NUMPAD layer, TAP MO(NM) for KC_UNDR (_)
 * .--------------------------------------------. .--------------------------------------------.
 * | Q      | W      | E      | R      | T      | | Y      | U      | I      | O      | P      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | A      | S      | D      | F      | G      | | H      | J      | K      | L      | ;      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | Z      | X      | C      | V      | B      | | N      | M      | ,      | .      | /      |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          | LGUI   | LCTRL  | ESC    | MO(FN) | | MO(NM) | BACKSP | RCTRL  | RGUI   |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          | TG(FN) | LALT   | SPACE  | LSHIFT | | RSHIFT | ENTER  | RALT   | TG(NM) |
 *          '-----------------------------------' '-----------------------------------'
 */
[BASE] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             KC_LGUI, KC_LCTL, KC_ESC,  _MO_FN,    _MO_NM,  KC_BSPC, KC_RCTL, KC_RGUI,
             _TG_FN,  KC_LALT, KC_SPC,  KC_LSPO,   KC_RSPC, KC_ENT,  KC_RALT, _TG_NM
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
 * contains keys that did not fit on BASE layer ([, ], \, ')
 * .--------------------------------------------. .--------------------------------------------.
 * |        |        |        |        |        | | XXXXXX | XXXXXX | [      | ]      | \      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * |        |        |        |        |        | | LEFT   | DOWN   | UP     | RIGHT  | '      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * |        |        |        |        |        | | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        |        | |        |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[FUNCTION] = LAYOUT(
    _______, _______, _______, _______, _______,   XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    _______, _______, _______, _______, _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             _______, _______, _______, _______,   _______, _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

/* MACRO LAYER
 * TAP INFO to get firmware information
 * TAP ALTESC to switch between apps in the same workspace (ALT+ESC)
 * TAP GUITAB to switch between apps (GUI+TAB)
 * .--------------------------------------------. .--------------------------------------------.
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | | TG(MS) | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | COPY   | XXXXXX | ALTESC | XXXXXX | | XXXXXX | GUITAB | XXXXXX | PASTE  | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | | XXXXXX | XXXXXX | XXXXXX | XXXXXX | INFO   |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        |        | |        |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[MACRO] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   _TG_MS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_COPY, XXXXXXX, _ALTESC, XXXXXXX,   XXXXXXX, _GUITAB, XXXXXXX, KC_PSTE, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _INFO,
             _______, _______, _______, _______,   _______, _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

/* MOUSE LAYER
 * TAP M_NW for KC_MS_UP + KC_MS_LEFT
 * TAP M_NE for KC_MS_UP + KC_MS_RIGHT
 * TAP M_SW for KC_MS_DOWN + KC_MS_LEFT
 * TAP M_SE for KC_MS_DOWN + KC_MS_RIGHT
 * TAP MS_LK to lock/unlock mouse selection
 * .--------------------------------------------. .--------------------------------------------.
 * | XXXXXX | XXXXXX | XXXXXX | BTN2   | XXXXXX | | XXXXXX | MS_NW  | MS_N   | MS_NE  | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | SLOW   | FAST   | BTN1   | XXXXXX | | XXXXXX | MS_W   | MS_LK  | MS_E   | XXXXXX |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | BTN3   | XXXXXX | | XXXXXX | MS_SW  | MS_S   | MS_SE  | XXXXXX |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        | TG(MS) | | TG(MS) |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[MOUSE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, XXXXXXX,   XXXXXXX, _MS_NW,  _MS_N,   _MS_NE,  XXXXXXX,
    XXXXXXX, KC_ACL0, KC_ACL2, KC_BTN1, XXXXXXX,   XXXXXXX, _MS_W,   _MS_LK,  _MS_E,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX,   XXXXXXX, _MS_SW,  _MS_S,   _MS_SE,  XXXXXXX,
             _______, _______, _______, _TG_MS,    _TG_MS,  _______, _______, _______,
             _______, _______, _______, _______,   _______, _______, _______, _______
),

};

static bool interrupted = false;

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

inline bool firmware_info(bool pressed) {
    if (pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
}

bool mo_ext(bool pressed, uint8_t layer, const char* str) {
    static uint16_t timer = 0;
    if (pressed) {
        timer = timer_read();
        interrupted = false;
        layer_on(layer);
    } else {
        if (!interrupted && (timer_elapsed(timer) < TAPPING_TERM)) {
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

    if (pressed) interrupted = true;

    switch (keycode) {
        case _MS_NE:
            return mousekey_diagonal(pressed, KC_MS_UP, KC_MS_RIGHT);

        case _MS_NW:
            return mousekey_diagonal(pressed, KC_MS_UP, KC_MS_LEFT);

        case _MS_SE:
            return mousekey_diagonal(pressed, KC_MS_DOWN, KC_MS_RIGHT);

        case _MS_SW:
            return mousekey_diagonal(pressed, KC_MS_DOWN, KC_MS_LEFT);

        case _MS_LK:
            return toggle_mouse_lock(pressed);

        case _MO_NM:
            return mo_ext(pressed, NUMPAD, PSTR("_"));

        case _MO_FN:
            return mo_ext(pressed, FUNCTION, PSTR(SS_TAP(X_TAB)));

        case _INFO:
            return firmware_info(pressed);
    }
    return true;
}

void keyboard_post_init_user() {
    set_led_off;
}

void alt_esc(qk_tap_dance_state_t* state, void* user_data) {
    if (!(get_mods() & MOD_BIT(KC_LALT))) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_ESCAPE));
    } else {
        SEND_STRING(SS_TAP(X_ESCAPE));
    }
}

void alt_esc_finished(qk_tap_dance_state_t* state, void* user_data) {
    SEND_STRING(SS_UP(X_LALT));
}

void gui_tab(qk_tap_dance_state_t* state, void* user_data) {
    if (!(get_mods() & MOD_BIT(KC_LGUI))) {
        SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB));
    } else {
        SEND_STRING(SS_TAP(X_TAB));
    }
}

void gui_tab_finished(qk_tap_dance_state_t* state, void* user_data) {
    SEND_STRING(SS_UP(X_LGUI));
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ALTESC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(alt_esc, alt_esc_finished, NULL, ALT_ESC_TIMEOUT),
    [TD_GUITAB] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(gui_tab, gui_tab_finished, NULL, GUI_TAB_TIMEOUT),
};

/* vim: set ts=4 sw=4 sts=4 et: */
