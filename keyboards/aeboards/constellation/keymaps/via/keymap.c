/* Copyright 2018 Jason Williams (Wilba)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "process_unicode_common.h"


enum { KC_CONFIG = SAFE_RANGE,
       KC_LOWER,
       KC_RAISE,
       KC_ADJUST,
       KC_NOMODE,
       KC_WIDE,
       KC_SCRIPT,
       KC_BLOCKS,
       KC_REGIONAL,
       KC_AUSSIE,
       KC_ZALGO,
       KC_SBOB,
       KC_REDACTED
};
#define KC_REDAC KC_REDACTED

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// Default layer
	[0] = LAYOUT_all(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_PSCR,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL,
		MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_HOME,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,   KC_END,
		KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_LALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

	// Fn1 Layer
	[1] = LAYOUT_all(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET,   KC_DEL,  KC_TRNS,
		KC_CAPS, KC_TRNS, KC_UP,   KC_TRNS, KC_REDAC,KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_PAUS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE,          KC_TRNS,
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ZALGO, KC_WIDE, KC_SCRIPT, KC_BLOCKS, KC_TRNS,                   KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NOMODE, KC_AUSSIE, KC_REGIONAL, KC_SBOB, KC_TRNS,           KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

uint16_t typing_mode = KC_NOMODE;
uint8_t prev_upper = 0;
uint8_t prev_lower = 0;
bool uppercase = false;


__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

void tap_code16_nomods(uint16_t kc) {
    uint8_t temp_mod = get_mods();
    clear_mods();
    clear_oneshot_mods();
    tap_code16(kc);
    set_mods(temp_mod);
}

void tap_unicode_glyph_nomods(uint32_t glyph) {
    uint8_t temp_mod = get_mods();
    clear_mods();
    clear_oneshot_mods();
    register_unicode(glyph);
    set_mods(temp_mod);
}

void keyboard_post_init_user(void) {
    typing_mode    = KC_NOMODE;
    uppercase      = false;
    prev_upper     = 0;
    prev_lower     = 0;
}

void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_WINC);
}

typedef uint32_t (*translator_function_t)(bool is_shifted, uint32_t keycode);

#define DEFINE_UNICODE_RANGE_TRANSLATOR(translator_name, lower_alpha, upper_alpha, zero_glyph, number_one, space_glyph) \
    static inline uint32_t translator_name(bool is_shifted, uint32_t keycode) {                                         \
        switch (keycode) {                                                                                              \
            case KC_A ... KC_Z:                                                                                         \
                return (is_shifted ? upper_alpha : lower_alpha) + keycode - KC_A;                                       \
            case KC_0:                                                                                                  \
                return zero_glyph;                                                                                      \
            case KC_1 ... KC_9:                                                                                         \
                return (number_one + keycode - KC_1);                                                                   \
            case KC_SPACE:                                                                                              \
                return space_glyph;                                                                                     \
        }                                                                                                               \
        return keycode;                                                                                                 \
    }

#define DEFINE_UNICODE_LUT_TRANSLATOR(translator_name, ...)                     \
    static inline uint32_t translator_name(bool is_shifted, uint32_t keycode) { \
        static const uint32_t translation[] = {__VA_ARGS__};                    \
        uint32_t              ret           = keycode;                          \
        if ((keycode - KC_A) < (sizeof(translation) / sizeof(uint32_t))) {      \
            ret = translation[keycode - KC_A];                                  \
        }                                                                       \
        return ret;                                                             \
    }

bool process_record_glyph_replacement(uint16_t keycode, keyrecord_t *record, translator_function_t translator) {
    uint8_t temp_mod   = get_mods();
    uint8_t temp_osm   = get_oneshot_mods();
    bool    is_shifted = (temp_mod | temp_osm) & MOD_MASK_SHIFT;
    if (((temp_mod | temp_osm) & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)) == 0) {
        if (KC_A <= keycode && keycode <= KC_Z) {
            if (record->event.pressed) {
                tap_unicode_glyph_nomods(translator(is_shifted, keycode));
            }
            return false;
        } else if (KC_1 <= keycode && keycode <= KC_0) {
            if (is_shifted) {  // skip shifted numbers, so that we can still use symbols etc.
                return process_record_keymap(keycode, record);
            }
            if (record->event.pressed) {
                register_unicode(translator(is_shifted, keycode));
            }
            return false;
        } else if (keycode == KC_SPACE) {
            if (record->event.pressed) {
                register_unicode(translator(is_shifted, keycode));
            }
            return false;
        }
    }
    return true;
}

DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_wide, 0xFF41, 0xFF21, 0xFF10, 0xFF11, 0x2003);
DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_script, 0x1D4EA, 0x1D4D0, 0x1D7CE, 0x1D7C1, 0x2002);
DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_boxes, 0x1F170, 0x1F170, '0', '1', 0x2002);
DEFINE_UNICODE_RANGE_TRANSLATOR(unicode_range_translator_regional, 0x1F1E6, 0x1F1E6, '0', '1', 0x2003);

DEFINE_UNICODE_LUT_TRANSLATOR(unicode_lut_translator_aussie,
                              0x0250,  // a
                              'q',     // b
                              0x0254,  // c
                              'p',     // d
                              0x01DD,  // e
                              0x025F,  // f
                              0x0183,  // g
                              0x0265,  // h
                              0x1D09,  // i
                              0x027E,  // j
                              0x029E,  // k
                              'l',     // l
                              0x026F,  // m
                              'u',     // n
                              'o',     // o
                              'd',     // p
                              'b',     // q
                              0x0279,  // r
                              's',     // s
                              0x0287,  // t
                              'n',     // u
                              0x028C,  // v
                              0x028D,  // w
                              0x2717,  // x
                              0x028E,  // y
                              'z',     // z
                              0x0269,  // 1
                              0x3139,  // 2
                              0x0190,  // 3
                              0x3123,  // 4
                              0x03DB,  // 5
                              '9',     // 6
                              0x3125,  // 7
                              '8',     // 8
                              '6',     // 9
                              '0'      // 0
);

bool process_record_aussie(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
    if ((KC_A <= keycode) && (keycode <= KC_0)) {
        if (record->event.pressed) {
            if (!process_record_glyph_replacement(keycode, record, unicode_lut_translator_aussie)) {
                tap_code16_nomods(KC_LEFT);
                return false;
            }
        }
    } else if (record->event.pressed && keycode == KC_SPACE) {
        tap_code16_nomods(KC_SPACE);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_ENTER) {
        tap_code16_nomods(KC_END);
        tap_code16_nomods(KC_ENTER);
        return false;
    } else if (record->event.pressed && keycode == KC_HOME) {
        tap_code16_nomods(KC_END);
        return false;
    } else if (record->event.pressed && keycode == KC_END) {
        tap_code16_nomods(KC_HOME);
        return false;
    } else if (record->event.pressed && keycode == KC_BSPC) {
        tap_code16_nomods(KC_DELT);
        return false;
    } else if (record->event.pressed && keycode == KC_DELT) {
        tap_code16_nomods(KC_BSPC);
        return false;
    } else if (record->event.pressed && keycode == KC_QUOT) {
        tap_unicode_glyph_nomods(is_shifted ? 0x201E : 0x201A);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_COMMA) {
        tap_unicode_glyph_nomods(is_shifted ? '<' : 0x2018);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_DOT) {
        tap_unicode_glyph_nomods(is_shifted ? '>' : 0x02D9);
        tap_code16_nomods(KC_LEFT);
        return false;
    } else if (record->event.pressed && keycode == KC_SLASH) {
        tap_unicode_glyph_nomods(is_shifted ? 0x00BF : '/');
        tap_code16_nomods(KC_LEFT);
        return false;
    }
    return true;
}

bool process_record_zalgo(uint16_t keycode, keyrecord_t *record) {
    if ((KC_A <= keycode) && (keycode <= KC_0)) {
        if (record->event.pressed) {
            tap_code16_nomods(keycode);

            int number = (rand() % (8 + 1 - 2)) + 2;
            for (int index = 0; index < number; index++) {
                uint16_t hex = (rand() % (0x036F + 1 - 0x0300)) + 0x0300;
                register_unicode(hex);
            }

            return false;
        }
    }
    return true;
}


bool process_record_spongebob(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ENTER && record->event.pressed) {
        uppercase = false;
        return process_record_keymap(keycode, record);
    }

    if (uppercase == false && record->event.pressed )  {
        uppercase = true;
        return process_record_keymap(keycode, record);
    }

    if((KC_A <= keycode) && (keycode <= KC_Z)) {
        if ( record->event.pressed ) {
            bool press = rand() % 2;

            if (prev_upper > 2) {           // if more than 3 lower's in a row print upper
                prev_upper = 0;
                press = false;
            } else if (prev_lower > 2) {    // if more than 3 upper's in a row print lower
                prev_lower = 0;
                press = true;
            }
            if (press) {
                prev_upper++;
                tap_code16(S(keycode));
                clear_mods();
            } else {
                prev_lower++;
                tap_code16(keycode);
            }
        }
        return false;
    }

    return process_record_keymap(keycode, record);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_NOMODE ... KC_SBOB:
            if (record->event.pressed) {
                if (typing_mode != keycode) {
                    typing_mode = keycode;
                } else {
                    typing_mode = KC_NOMODE;
                }
            }
            break;
        case KC_REDACTED:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_UP) SS_LCTL("a") SS_DELAY(50) SS_TAP(X_DEL) SS_DELAY(50) "[redacted]" SS_TAP(X_ENT));
            }
            return false;
    }

    if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
        return true;
    }

    if (((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) && record->tap.count) {
        keycode &= 0xFF;
    }

    if (typing_mode == KC_WIDE) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            return process_record_glyph_replacement(keycode, record, unicode_range_translator_wide);
        }
    } else if (typing_mode == KC_SCRIPT) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            return process_record_glyph_replacement(keycode, record, unicode_range_translator_script);
        }
    } else if (typing_mode == KC_BLOCKS) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            return process_record_glyph_replacement(keycode, record, unicode_range_translator_boxes);
        }
    } else if (typing_mode == KC_REGIONAL) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            if (!process_record_glyph_replacement(keycode, record, unicode_range_translator_regional)) {
                wait_us(500);
                tap_unicode_glyph_nomods(0x200C);
                return false;
            }
        }
    } else if (typing_mode == KC_AUSSIE) {
        return process_record_aussie(keycode, record);
    } else if (typing_mode == KC_ZALGO) {
        return process_record_zalgo(keycode, record);
    } else if (typing_mode == KC_SBOB) {
        return process_record_spongebob(keycode, record);
    }

    return true;

}
