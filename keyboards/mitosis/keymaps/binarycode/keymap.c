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
    // tmux
    KC_CTRLA,
    KC_CTRLB
};

// Tap dances
enum {
    TD_L_LOWER,
    TD_R_LOWER
};

// Tap dance states
enum {
    UNKNOWN,
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// For consistency with diagonal mouse keys
#define KC_MS_N KC_MS_UP
#define KC_MS_S KC_MS_DOWN
#define KC_MS_W KC_MS_LEFT
#define KC_MS_E KC_MS_RIGHT

// Toggle layout
#define KC_MOUSE TG(MOUSE)

// Tap dance
#define KC_L_LWR TD(TD_L_LOWER)
#define KC_R_LWR TD(TD_R_LOWER)

// Copy-paste
#define KC_CTRLC LCTL(KC_C)
#define KC_CTRLV LCTL(KC_V)

// Special functions
#define KC_MNVIM LCTL(KC_F7)
#define KC_FINGR LCTL(KC_F9)
#define KC_TMUX1 LCTL(KC_F1)
#define KC_TMUX2 LCTL(KC_F2)
#define KC_TMUX3 LCTL(KC_F3)

#define KC_    KC_TRNS
#define KC_XXX KC_NO

#define MOD_MASK_SHIFT (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE LAYER
 * HOLD NAV for NAVIGATION layer, TAP NAV for KC_TAB
 * HOLD NUM for NUMPAD layer, TAP NUM for KC_UNDR (_)
 */
[BASE] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
        Q   ,   W   ,   E   ,   R   ,   T   ,        Y   ,   U   ,   I   ,   O   ,   P   ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
        A   ,   S   ,   D   ,   F   ,   G   ,        H   ,   J   ,   K   ,   L   , SCLN  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
        Z   ,   X   ,   C   ,   V   ,   B   ,        N   ,   M   , COMM  ,  DOT  , SLSH  ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
               XXX  , CTRLC ,  ESC  , L_LWR ,      R_LWR , BSPC  , RCTL  , RGUI  ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
              CTRLA , CTRLV ,  SPC  , LSFT  ,      RSFT  ,  ENT  , RALT  ,  XXX
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* NUMPAD LAYER
 */
[NUMPAD] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
       GRV  ,   7   ,   8   ,   9   , MINS  ,      RBRC  , RPRN  , RCBR  ,       ,       ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,   4   ,   5   ,   6   ,  EQL  ,      LBRC  , LPRN  , LCBR  ,       ,       ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,   1   ,   2   ,   3   ,   0   ,       TAB  , UNDS  ,       ,       ,       ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       ,       ,       ,            ,       ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
                    ,       ,       ,  TAB  ,            ,       ,       ,
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* NAVIGATION LAYER
 * contains keys that did not fit on BASE layer ([, ], \, ')
 */
[NAVIGATION] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
            ,  F7   ,  F8   ,  F9   ,  F12  ,       XXX  ,  XXX  , LBRC  , RBRC  , BSLS  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
            ,  F4   ,  F5   ,  F6   ,  F11  ,      LEFT  , DOWN  ,  UP   , RGHT  , QUOT  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
            ,  F1   ,  F2   ,  F3   ,  F10  ,      HOME  , PGDN  , PGUP  , END   ,  XXX  ,
//  └───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┘
                    ,       ,       ,       ,            ,  DEL  ,       ,       ,
//          ├───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┤
                    ,       ,       ,       ,      UNDS  ,       ,       ,
//          └───────┴───────┴───────┴───────┘    └───────┴───────┴───────┴───────┘
),

/* MACRO LAYER
 * TAP INFO to get firmware information
 */
[MACRO] = LAYOUT_kc(
//  ┌───────┬───────┬───────┬───────┬───────┐    ┌───────┬───────┬───────┬───────┬───────┐
       XXX  ,  XXX  ,  XXX  ,  XXX  ,  XXX  ,      PSCR  ,  XXX  ,  XXX  ,  XXX  ,  XXX  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  ,  XXX  , MNVIM , FINGR , SCROL ,       XXX  ,  XXX  , MOUSE ,  XXX  ,  XXX  ,
//  ├───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┤
       XXX  , TMUX1 , TMUX2 , TMUX3 ,  XXX  ,       XXX  ,  XXX  ,  XXX  ,  XXX  , INFO  ,
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

inline bool tmux_slave(bool pressed) {
    if (pressed) {
        register_code(KC_LCTL);
        tap_code(KC_A);
        /*register_code(KC_A);*/
        /*SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_A));*/
    } else {
        /*unregister_code(KC_A);*/
        unregister_code(KC_LCTL);
        /*SEND_STRING(SS_UP(X_A) SS_UP(X_LCTL));*/
    }
    return false;
}

inline bool tmux_master(bool pressed) {
    if (pressed) {
        register_code(KC_LCTL);
        tap_code(KC_B);
        /*register_code(KC_B);*/
        /*SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_B));*/
    } else {
        /*unregister_code(KC_B);*/
        unregister_code(KC_LCTL);
        /*SEND_STRING(SS_UP(X_B) SS_UP(X_LCTL));*/
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

        case KC_CTRLA:
            return tmux_slave(pressed);

        case KC_CTRLB:
            return tmux_master(pressed);
    }
    return true;
}

void keyboard_post_init_user() {
    set_led_off;
}

int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) return SINGLE_HOLD;
        else return SINGLE_TAP;
    }
    if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->pressed) return TRIPLE_HOLD;
        else return TRIPLE_TAP;
    }
    return UNKNOWN;
}

static int l_lower_state;

void l_lower_tap(qk_tap_dance_state_t *state, void *user_data) {
    layer_on(NAVIGATION);
}

void l_lower_finished(qk_tap_dance_state_t *state, void *user_data) {
    /*l_lower_state = cur_dance(state);*/
    /*switch (l_lower_state) {*/
        /*case SINGLE_TAP:*/
            /*register_code(KC_TAB);*/
            /*break;*/
    /*}*/
}

void l_lower_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (l_lower_state) {
        /*case DOUBLE_HOLD:*/
            /*break;*/

        /*case SINGLE_TAP:*/
            /*unregister_code(KC_TAB);*/
            // intentionally no break to make sure the layer is off

        default:
            layer_off(NAVIGATION);
            break;
    }
}

static int r_lower_state;

void r_lower_tap(qk_tap_dance_state_t *state, void *user_data) {
    layer_on(NUMPAD);
}

void r_lower_finished(qk_tap_dance_state_t *state, void *user_data) {
    /*r_lower_state = cur_dance(state);*/
    /*switch (r_lower_state) {*/
        /*case SINGLE_TAP:*/
            /*SEND_STRING("_");*/
            /*break;*/
    /*}*/
}

void r_lower_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (r_lower_state) {
        /*case DOUBLE_HOLD:*/
            /*break;*/

        default:
            layer_off(NUMPAD);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_L_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(l_lower_tap, l_lower_finished, l_lower_reset),
    [TD_R_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(r_lower_tap, r_lower_finished, r_lower_reset),
};

/* vim: set ts=4 sw=4 sts=4 et: */
