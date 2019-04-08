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

// TODO: TEST the LED logic still works
// TODO: leader-v for version? or at least version format
// TODO: copy-paste keycodes - test they work on linux, maybe combine with ctrl/alt
// TODO: proper file format - headers etc
// TODO: play with autoshift

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
    // Brackets + shift-tap
    XX_LBRC,
    XX_LCBR,
    XX_LABK,
    // Arrows + shift-tap
    XX_UP,
    XX_DOWN,
    XX_LEFT,
    XX_RGHT,
    // Mouse keys + shift-tap
    XX_M_N,
    XX_M_S,
    XX_M_W,
    XX_M_E,
    // Mouse selection lock
    XX_M_LK,
    // Firmware info
    XX_INFO,
    // Application switching
    XX_SW_L,
    XX_SW_G
};

// Merge copy-paste with modifiers
#define XX_LCTL LCTL_T(KC_COPY)
#define XX_RCTL RCTL_T(KC_COPY)
#define XX_LALT LALT_T(KC_PASTE)
#define XX_RALT RALT_T(KC_PASTE)

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
 * TODO: KC_0 hides LCTRL - is that a problem?
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
 * TAP LEFT for LEFT, SHIFT-TAP LEFT for HOME
 * TAP DOWN for DOWN, SHIFT-TAP DOWN for PGDOWN
 * TAP UP for UP, SHIFT-TAP UP for PGUP
 * TAP RIGHT for RIGHT, SHIFT-TAP RIGHT for END
 * TAP LBRC for LBRC, SHIFT-TAP LBRC for RBRC
 * TAP LCBR for LCBR, SHIFT-TAP LCBR for RCBR
 * TAP LABK for LABK, SHIFT-TAP LABK for RABK
 * .--------------------------------------------. .--------------------------------------------.
 * |        |        |        |        |        | | XXXXXX | XXXXXX | [      | ]      | \      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * |        |        |        |        |        | | LEFT   | DOWN   | UP     | RIGHT  | '      |
 * |--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------|
 * |        |        |        |        |        | | [ / ]  | { / }  | < / >  | XXXXXX | /      |
 * '--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------'
 *          |        |        |        |        | |        |        |        |        |
 *          |--------+--------+--------+--------| |--------+--------+--------+--------|
 *          |        |        |        |        | |        |        |        |        |
 *          '-----------------------------------' '-----------------------------------'
 */
[FUNCTION] = LAYOUT(
    _______, _______, _______, _______, _______,   XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______,   XX_LEFT, XX_DOWN, XX_UP,   XX_RGHT, KC_QUOT,
    _______, _______, _______, _______, _______,   XX_LBRC, XX_LCBR, XX_LABK, XXXXXXX, KC_SLSH,
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
 * TAP M_N for KC_MS_UP, SHIFT-TAP M_N for KC_MS_WH_UP
 * TAP M_S for KC_MS_DOWN, SHIFT-TAP M_S for KC_MS_WH_DOWN
 * TAP M_W for KC_MS_LEFT, SHIFT-TAP M_W for KC_MS_WH_LEFT
 * TAP M_E for KC_MS_RIGHT, SHIFT-TAP M_E for KC_MS_WH_RIGHT
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

static bool mouse_lock = false;

void mousekey_diagonal(bool pressed, uint16_t key1, uint16_t key2) {
    if (pressed) {
        mousekey_on(key1);
        mousekey_on(key2);
    } else {
        mousekey_off(key1);
        mousekey_off(key2);
    }
    mousekey_send();
}

void shift_tap(bool pressed, uint16_t* current, uint16_t unshifted, uint16_t shifted) {
    if (pressed) {
        if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {
          *current = shifted;
        } else {
          *current = unshifted;
        }
        register_code(*current);
    } else {
        unregister_code(*current);
    }
}

uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, NUMPAD, FUNCTION, MACRO);

    uint8_t layer = biton32(state);

    // TODO: TEST if this is enough or we need the full check
    if (mouse_lock) {
      mouse_lock = false;
      mousekey_off(KC_BTN1);
    }
    /*if (mouse_lock && !(state & (1UL << MOUSE))) mouse_lock = false;*/

    switch (layer) {
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
    static bool lock = false;

    static uint16_t lbrc_keycode  = KC_LBRC;
    static uint16_t lcbr_keycode  = KC_LCBR;
    static uint16_t labk_keycode  = KC_LABK;
    static uint16_t up_keycode    = KC_UP;
    static uint16_t down_keycode  = KC_DOWN;
    static uint16_t left_keycode  = KC_LEFT;
    static uint16_t right_keycode = KC_RGHT;
    static uint16_t north_keycode = KC_MS_UP;
    static uint16_t south_keycode = KC_MS_DOWN;
    static uint16_t west_keycode  = KC_MS_LEFT;
    static uint16_t east_keycode  = KC_MS_RIGHT;

    static uint16_t unds_timer   = 0;
    static uint16_t tab_timer    = 0;
    static bool unds_interrupted = false;
    static bool tab_interrupted  = false;

    if (keycode != XX_L_NM) unds_interrupted = true;
    if (keycode != XX_L_FN) tab_interrupted  = true;

    switch (keycode) {
        // Diagonal mouse keys
        case XX_M_NE:
            mousekey_diagonal(record->event.pressed, KC_MS_UP, KC_MS_RIGHT);
            return false;

        case XX_M_NW:
            mousekey_diagonal(record->event.pressed, KC_MS_UP, KC_MS_LEFT);
            return false;

        case XX_M_SE:
            mousekey_diagonal(record->event.pressed, KC_MS_DOWN, KC_MS_RIGHT);
            return false;

        case XX_M_SW:
            mousekey_diagonal(record->event.pressed, KC_MS_DOWN, KC_MS_LEFT);
            return false;

        // Key lock
        case XX_LOCK:
            lock = record->event.pressed;
            return false;

        // Layer modifiers
        case XX_L_NM:
            if (record->event.pressed) {
                unds_timer       = timer_read();
                unds_interrupted = false;
                layer_on(NUMPAD);
            } else if (!lock) {
                if (!unds_interrupted && (timer_elapsed(unds_timer) < TAPPING_TERM)) {
                    register_code(KC_LSFT);
                    register_code(KC_MINS);
                    unregister_code(KC_MINS);
                    unregister_code(KC_LSFT);
                }
                layer_off(NUMPAD);
            }
            return false;

        case XX_L_FN:
            if (record->event.pressed) {
                tab_timer       = timer_read();
                tab_interrupted = false;
                layer_on(FUNCTION);
            } else if (!lock) {
                if (!tab_interrupted && (timer_elapsed(tab_timer) < TAPPING_TERM)) {
                    register_code(KC_TAB);
                    unregister_code(KC_TAB);
                }
                layer_off(FUNCTION);
            }
            return false;

        // Brackets + shift-tap
        case XX_LBRC:
            shift_tap(record->event.pressed, &lbrc_keycode, KC_LBRC, KC_RBRC);
            return false;

        case XX_LCBR:
            shift_tap(record->event.pressed, &lcbr_keycode, KC_LCBR, KC_RCBR);
            return false;

        case XX_LABK:
            shift_tap(record->event.pressed, &labk_keycode, KC_LABK, KC_RABK);
            return false;

        // Arrows + shift-tap
        case XX_UP:
            shift_tap(record->event.pressed, &up_keycode, KC_UP, KC_PGUP);
            return false;

        case XX_DOWN:
            shift_tap(record->event.pressed, &down_keycode, KC_DOWN, KC_PGDOWN);
            return false;

        case XX_LEFT:
            shift_tap(record->event.pressed, &left_keycode, KC_LEFT, KC_HOME);
            return false;

        case XX_RGHT:
            shift_tap(record->event.pressed, &right_keycode, KC_RIGHT, KC_END);
            return false;

        // Mouse keys + shift-tap
        case XX_M_N:
            shift_tap(record->event.pressed, &north_keycode, KC_MS_UP, KC_MS_WH_UP);
            return false;

        case XX_M_S:
            shift_tap(record->event.pressed, &south_keycode, KC_MS_DOWN, KC_MS_WH_DOWN);
            return false;

        case XX_M_W:
            shift_tap(record->event.pressed, &west_keycode, KC_MS_LEFT, KC_MS_WH_LEFT);
            return false;

        case XX_M_E:
            shift_tap(record->event.pressed, &east_keycode, KC_MS_RIGHT, KC_MS_WH_RIGHT);
            return false;

        // Mouse lock
        case XX_M_LK:
            mouse_lock = !mouse_lock;
            if (mouse_lock) {
              mousekey_on(KC_BTN1);
            } else {
              mousekey_off(KC_BTN1);
            }
            return false;

        // Firmware info
        case XX_INFO:
            if (record->event.pressed) {
              SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
            }
            return false;

        // Application switching
        case XX_SW_L:
            if (record->event.pressed) {
              SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_ESCAPE) SS_UP(X_LALT));
            }
            return false;

        case XX_SW_G:
            if (record->event.pressed) {
              SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB) SS_UP(X_LALT));
            }
            return false;
    }
    return true;
}
