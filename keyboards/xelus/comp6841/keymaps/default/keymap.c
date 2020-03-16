// Default layout for COMP6841
#include QMK_KEYBOARD_H

enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL,
  MY_OTHER_MACRO
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/\n");
      } else {
        // when keycode QMKURL is released
      }
      break;
    case MY_OTHER_MACRO:
      if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ac")); // selects all and copies
      }
      break;
  }
  return true;
};

void keyboard_pre_init_user(void) {
    SEND_STRING(SS_LCTL("a"));
    //SEND_STRING(QMKBEST);
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_all(
        KC_ESC,  QMK_BEST, QMK_URL,   MY_OTHER_MACRO,    KC_4,    KC_5,    KC_6
    )
};
