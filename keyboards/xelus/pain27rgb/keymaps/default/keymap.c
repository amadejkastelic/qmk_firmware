// Default layout for Zeal60
#include QMK_KEYBOARD_H

// For readability.
#define _______ KC_TRNS
#define   _x_   KC_NO
#define AUD_PRV LCTL(KC_MPRV) // Previous music track
#define AUD_PLY LCTL(KC_MPLY) // Pause music
#define AUD_NXT LCTL(KC_MNXT) // Next music track

// Zeal60-specific keys:
//  EF_INC, EF_DEC,   // next/previous backlight effect
//  H1_INC, H1_DEC,   // Color 1 hue increase/decrease
//  S1_INC, S1_DEC,   // Color 1 saturation increase/decrease
//  H2_INC, H2_DEC,   // Color 2 hue increase/decrease
//  S2_INC, S2_DEC,   // Color 2 saturation increase/decrease
//  BR_INC, BR_DEC,   // backlight brightness increase/decrease

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Default layer: Pressing caps-lock momentarily switches to Layer 1.
// This is the default layer. Pressing an empty keycode on another layer will take you here.
    [0] = {
        { KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,  KC_P },
        { KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   _x_ },
        { KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    _x_,     _x_,    _x_ },
        { _x_   ,  _x_ ,    _x_ ,    _x_ ,    KC_V,    _x_ ,    _x_ ,    _x_,     _x_,    _x_ }
    },

// Layer 1: Pressing enter switches to layer 2, where backlight controls live.
// This is a momentary layer: once you let go of caps, you'll be back in layer 1.
    [1] = {
        {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9  },
        {KC_CAPS, KC_NO  , KC_UP  , KC_NO  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
        {KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
        {KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI}
    },     

// Layer 2: Zeal60 and backlight configuration. (Get here quickly by pressing Caps+Enter from Layer 1.)
// This is a persistent layer. Get back to the default layer by pressing enter.
    [2] = {
        {RESET,   EF_DEC,  EF_INC,  BR_DEC,  BR_INC,  ES_DEC,  ES_INC,  _______, _______, _______},
        {_______, H1_DEC,  H1_INC,  S1_DEC,  S1_INC,  _______, _______, _______, _______, _______},
        {_______, H2_DEC,  H2_INC,  S2_DEC,  S2_INC,  _______, _______, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    }
};
