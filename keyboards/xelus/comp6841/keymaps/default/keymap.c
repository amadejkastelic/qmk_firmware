// Default layout for Dawn60
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Default layer: Pressing caps-lock momentarily switches to Layer 1.
// This is the default layer. Pressing an empty keycode on another layer will take you here.
    [0] = LAYOUT_60_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6
    )

};
