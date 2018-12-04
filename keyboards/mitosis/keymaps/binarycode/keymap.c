#include "mitosis.h"

// Mousekeys
#define MOUSEKEY_DELAY 300
#define MOUSEKEY_INTERNAL 50
#define MOUSEKEY_MAX_SPEED 20
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

// Layers
#define BASE 0
#define NUM  1
#define FN   2

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE LAYER
   * .--------------------------------------------..--------------------------------------------.
   * | Q      | W      | E      | R      | T      || Y      | U      | I      | O      | P      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | A      | S      | D      | F      | G      || J      | H      | K      | L      | ;      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | Z      | X      | C      | V      | B      || N      | M      | ,      | .      | /      |
   * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
   *          |        |        | LCTRL  | SPACE  || LSHIFT |        |        | BACKSP |
   *          |--------+--------+--------+--------||--------+--------+--------+--------|
   *          |        | LGUI   | ESCAPE | FN     || NUM    | ENTER  |        |        |
   *          '-----------------------------------''-----------------------------------'
   */
  [BASE] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             XXXXXXX, XXXXXXX, KC_LCTL, KC_SPC,         KC_LSFT, XXXXXXX, XXXXXXX, KC_BSPC,
             XXXXXXX, KC_LGUI, KC_ESC,  MO(FN),         MO(NUM), KC_ENT,  XXXXXXX, XXXXXXX
  ),

  /* NUMBER LAYER
   * .--------------------------------------------..--------------------------------------------.
   * | TAB    |        |        | -      | =      || ]      | pad *  | pad +  | pad -  | [      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | 1      | 2      | 3      | 4      | 5      || 6      | 7      | 8      | 9      | 0      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | F1     | F2     | F3     | F4     | F5     || F6     | F7     | F8     | F9     | F10    |
   * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
   *          | F11    | F12    |        |        ||        |        |        |        |
   *          |--------+--------+--------+--------||--------+--------+--------+--------|
   *          |        |        |        |        ||        |        |        |        |
   *          '-----------------------------------''-----------------------------------'
   */
  [NUM] = LAYOUT(
    KC_TAB,  _______, _______, KC_MINS, KC_EQL,        KC_RBRC, KC_PAST, KC_PPLS, KC_PMNS, KC_LBRC,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
             KC_F11,  KC_F12,  _______, _______,       _______, _______, _______, _______,
             _______, _______, _______, _______,       _______, _______, _______, _______
  ),


  /* FN LAYER
   * .--------------------------------------------..--------------------------------------------.
   * | `      |        | MS_U   |        |        || WH_U   | WH_L   | BTN3   | WH_R   | [      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * |        | MS_L   | MS_D   | MS_R   |        || WH_D   | BTN1   | BTN2   |        | '      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | APP    | MPRV   | MPLY   | MSTP   | MNXT   ||        | BSPC   | DEL    | INS    | \      |
   * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
   *          | VOLU   |        |        |        ||        |        | PGUP   |        |
   *          |--------+--------+--------+--------||--------+--------+--------+--------|
   *          | VOLD   |        |        |        ||        | HOME   | PGDN   | END    |
   *          '-----------------------------------''-----------------------------------'
   */
  [FN] = LAYOUT(
    KC_GRV,  _______, KC_MS_U, _______, _______,       KC_WH_U, KC_WH_L, KC_BTN3, KC_WH_R, KC_LBRC,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,       KC_WH_D, KC_BTN1, KC_BTN2, _______, KC_QUOT,
    KC_APP,  KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,       _______, KC_BSPC, KC_DEL,  KC_INS,  KC_BSLS,
             KC_VOLU, _______, _______, _______,       _______, _______, KC_PGUP, _______,
             KC_VOLD, _______, _______, _______,       _______, KC_HOME, KC_PGDN, KC_END
  ),
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case BASE:
        set_led_off;
        break;
      case FN:
        set_led_blue;
        break;
      case NUM:
        set_led_red;
        break;
      default:
        break;
    }
};
