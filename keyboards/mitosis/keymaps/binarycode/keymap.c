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

// Layers
enum {
  BASE,
  NUMPAD,
  NAVIGATION,
  MACRO,
  MOUSE
};

// Custom keycodes
enum {
    _NOP = SAFE_RANGE,
    // Diagonal mouse keys
    KC_MS_NE,
    KC_MS_NW,
    KC_MS_SE,
    KC_MS_SW,
    // Mouse selection lock
    KC_MS_LK,
    // Firmware info
    KC_INFO,
    // tmux copy mode
    KC_SCROL,
};

// For consistency with diagonal mouse keys
#define KC_MS_N KC_MS_UP
#define KC_MS_S KC_MS_DOWN
#define KC_MS_W KC_MS_LEFT
#define KC_MS_E KC_MS_RIGHT

// Toggle layout
#define KC_MOUSE TG(MOUSE)
#define KC_L_LWR LT(NAVIGATION, KC_ESC)
#define KC_R_LWR LT(NUMPAD, KC_ENT)

// Special functions
#define KC_MNVIM LCTL(KC_F7)
#define KC_FINGR LCTL(KC_F9)
#define KC_TMUX1 LCTL(KC_F1)
#define KC_TMUX2 LCTL(KC_F2)
#define KC_TMUX3 LCTL(KC_F3)

// Switch windows
#define KC_SWTCH LALT(KC_ESC)

// Switch workspaces
#define KC_WSPC1 LGUI(KC_1)
#define KC_WSPC2 LGUI(KC_2)
#define KC_WSPC3 LGUI(KC_3)

#define KC_    KC_TRNS
#define KC_XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE LAYER
 * HOLD L_LWR for NAVIGATION layer, TAP L_LWR for KC_ESC
 * HOLD R_LWR for NUMPAD layer, TAP R_LWR for KC_ENT
 * TODO: double shift for new layer
 * TODO: L_LWR+RSFT, R_LWR+LSFT
 */
[BASE] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
        Q   ,   W   ,   E   ,   R   ,   T   ,        Y   ,   U   ,   I   ,   O   ,   P   ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
        A   ,   S   ,   D   ,   F   ,   G   ,        H   ,   J   ,   K   ,   L   , SCLN  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
        Z   ,   X   ,   C   ,   V   ,   B   ,        N   ,   M   , COMM  ,  DOT  , SLSH  ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       ,  SPC  , L_LWR ,      R_LWR ,  TAB  ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
              LGUI  , LALT  , LCTL  , LSFT  ,      RSFT  , RCTL  , RALT  , RGUI
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* NUMPAD LAYER
 * TODO: 2 unassigned keys
 * TODO: what can we do on the right side???
 */
[NUMPAD] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
       GRV  ,   7   ,   8   ,   9   , MINS  ,            ,       ,       ,       ,       ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,   4   ,   5   ,   6   ,  EQL  ,            ,       ,       ,       ,       ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,   1   ,   2   ,   3   ,   0   ,            ,       ,       ,       ,       ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       , BSPC  ,       ,            ,       ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
                    , LCBR  , LBRC  , LPRN  ,            ,       ,       ,
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* NAVIGATION LAYER
 * contains keys that did not fit on BASE layer ([, ], \, ')
 * TODO: 3 unassigned keys
 * TODO: not sure if this is a right place for DEL
 */
[NAVIGATION] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
            ,  F7   ,  F8   ,  F9   ,  F12  ,       XXX  ,  XXX  , LBRC  , RBRC  , BSLS  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
            ,  F4   ,  F5   ,  F6   ,  F11  ,      LEFT  , DOWN  ,  UP   , RGHT  , QUOT  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
            ,  F1   ,  F2   ,  F3   ,  F10  ,      HOME  , PGDN  , PGUP  , END   ,  XXX  ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       ,  DEL  ,       ,            ,       ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
                    ,       ,       ,       ,      RPRN  , RBRC  , RCBR  ,
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* MACRO LAYER
 * TAP INFO to get firmware information
 */
[MACRO] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
       XXX  ,  XXX  ,  XXX  ,  XXX  ,  XXX  ,      WSPC1 ,  XXX  ,  XXX  ,  XXX  , PSCR  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,  XXX  , MNVIM , FINGR , SCROL ,      WSPC2 , SWTCH , MOUSE ,  XXX  ,  XXX  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  , TMUX1 , TMUX2 , TMUX3 ,  XXX  ,      WSPC3 ,  XXX  ,  XXX  ,  XXX  , INFO  ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       ,       ,       ,            ,       ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
                    ,       ,       ,       ,            ,       ,       ,
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* MOUSE LAYER
 * TAP M_NW for KC_MS_UP + KC_MS_LEFT
 * TAP M_NE for KC_MS_UP + KC_MS_RIGHT
 * TAP M_SW for KC_MS_DOWN + KC_MS_LEFT
 * TAP M_SE for KC_MS_DOWN + KC_MS_RIGHT
 * TAP MS_LK to lock/unlock mouse selection
 */
[MOUSE] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
       XXX  , BTN3  , BTN2  , BTN1  ,  XXX  ,       XXX  , MS_NW , MS_N  , MS_NE ,  XXX  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,  XXX  ,  XXX  , COPY  ,  XXX  ,       XXX  , MS_W  , MS_LK , MS_E  ,  XXX  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  , ACL0  , ACL1  , ACL2  ,  XXX  ,       XXX  , MS_SW , MS_S  , MS_SE ,  XXX  ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       ,       , MOUSE ,      MOUSE ,       ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
                    ,       ,       ,       ,            ,       ,       ,
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
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

inline bool firmware_info(bool pressed) {
    if (pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
}

inline bool tmux_copy_mode(bool pressed) {
    if (pressed) {
        SEND_STRING(SS_LCTRL("a") "[");
    }
    return false;
}

uint32_t layer_state_set_user(uint32_t state) {
    toggle_mouse_lock(false);

    state = update_tri_layer_state(state, NUMPAD, NAVIGATION, MACRO);

    switch (biton32(state)) {
        case BASE:
            set_led_off;
            break;
        case NUMPAD:
            set_led_blue;
            break;
        case NAVIGATION:
            set_led_red;
            break;
        case MACRO:
            set_led_magenta;
            break;
        case MOUSE:
            set_led_green;
            tap_code16(KC_ACL2);
            break;
        default:
            set_led_white;
            break;
    }

    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool pressed = record->event.pressed;

    switch (keycode) {
        case KC_MS_NE:
            return mousekey_diagonal(pressed, KC_MS_UP, KC_MS_RIGHT);

        case KC_MS_NW:
            return mousekey_diagonal(pressed, KC_MS_UP, KC_MS_LEFT);

        case KC_MS_SE:
            return mousekey_diagonal(pressed, KC_MS_DOWN, KC_MS_RIGHT);

        case KC_MS_SW:
            return mousekey_diagonal(pressed, KC_MS_DOWN, KC_MS_LEFT);

        case KC_MS_LK:
            return toggle_mouse_lock(pressed);

        case KC_INFO:
            return firmware_info(pressed);

        case KC_SCROL:
            return tmux_copy_mode(pressed);
    }
    return true;
}

void keyboard_post_init_user() {
    set_led_off;
}

/* vim: set ts=4 sw=4 sts=4 et: */
