// Default layout for COMP6841
#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
    SEND_STRING("Wow is that brute force? It's doomed.\n");
    while(1){}
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_all(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7
    )
};
