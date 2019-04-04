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
#define GUI  3

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define KC_TMUX LCTL(KC_A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE LAYER
   * .--------------------------------------------..--------------------------------------------.
   * | Q      | W      | E      | R      | T      || Y      | U      | I      | O      | P      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | A      | S      | D      | F      | G      || J      | H      | K      | L      | ;      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | Z      | X      | C      | V      | B      || N      | M      | ,      | .      | /      |
   * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
   *          | TMUX   | LCTRL  | ESCAPE | FN     || NUM    | BACKSP | RCTRL  | TAB    |
   *          |--------+--------+--------+--------||--------+--------+--------+--------|
   *          | LALT   | LGUI   | SPACE  | LSHIFT || RSHIFT | ENTER  | RCTRL  | RALT   |
   *          '-----------------------------------''-----------------------------------'
   */
  [BASE] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             KC_TMUX, KC_LCTL, KC_ESC,  MO(FN),         MO(NUM), KC_BSPC, KC_RCTL, KC_TAB,
             KC_LALT, KC_LGUI, KC_SPC,  KC_LSFT,        KC_RSFT, KC_ENT,  KC_RCTL, KC_RALT
  ),

  /* NUMBER LAYER
   * .--------------------------------------------..--------------------------------------------.
   * |        |        |        | -      | =      || ]      |        |        |        | [      |
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
    _______, _______, _______, KC_MINS, KC_EQL,        KC_RBRC, _______, _______, _______, KC_LBRC,
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
             KC_F11,  KC_F12,  _______, _______,       _______, _______, _______, _______,
             _______, _______, _______, _______,       _______, _______, _______, _______
  ),


  /* FN LAYER
   * .--------------------------------------------..--------------------------------------------.
   * | `      |        |        |        |        ||        |        |        |        |        |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * |        |        |        |        |        || LEFT   | DOWN   | UP     | RIGHT  | '      |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * |        |        |        |        |        ||        |        |        |        | \      |
   * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
   *          |        |        |        |        ||        |        |        |        |
   *          |--------+--------+--------+--------||--------+--------+--------+--------|
   *          |        |        |        |        ||        |        |        |        |
   *          '-----------------------------------''-----------------------------------'
   */
  [FN] = LAYOUT(
    KC_GRV,  _______, _______, _______, _______,       _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, KC_BSLS,
             _______, _______, _______, _______,       _______, _______, _______, TG(GUI),
             _______, _______, _______, _______,       _______, _______, _______, _______
  ),


  /* GUI LAYER
   * .--------------------------------------------..--------------------------------------------.
   * |        |        |        |        |        ||        |        |        |        |        |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * | MEDUIM | FAST   | BTN2   | BTN1   |        || MS_L   | MS_D   | MS_U   | MS_R   |        |
   * |--------+--------+--------+--------+--------||--------+--------+--------+--------+--------|
   * |        |        |        |        |        ||        |        |        |        |        |
   * '--------+--------+--------+--------+--------||--------+--------+--------+--------+--------'
   *          |        |        |        |        ||        |        |        | BASE   |
   *          |--------+--------+--------+--------||--------+--------+--------+--------|
   *          |        |        |        |        ||        |        |        |        |
   *          '-----------------------------------''-----------------------------------'
   */
  [GUI] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ACL0, KC_ACL2, KC_BTN2, KC_BTN1, XXXXXXX,       KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, TG(GUI),
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
      case GUI:
        set_led_green;
        break;
      default:
        break;
    }
};
