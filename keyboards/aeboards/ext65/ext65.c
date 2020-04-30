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

// Nothing to see here, move along... ;-)

#include <string.h>
#include <quantum.h>
#include <process_unicode_common.h>
#include "ext65.h"

uint16_t repeat_mode;

void tap_code16_nomods(uint8_t kc) {
    uint8_t temp_mod = get_mods();
    clear_mods();
    clear_oneshot_mods();
    tap_code16(kc);
    set_mods(temp_mod);
}

void tap_unicode_glyph(uint32_t glyph) {
    unicode_input_start();
    register_hex32(glyph);
    unicode_input_finish();
}

void tap_unicode_glyph_nomods(uint32_t glyph) {
    uint8_t temp_mod = get_mods();
    clear_mods();
    clear_oneshot_mods();
    tap_unicode_glyph(glyph);
    set_mods(temp_mod);
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

void tzarc_common_init(void) {
    repeat_mode    = KC_NOMODE;
}

void keyboard_post_init_user(void) {
    tzarc_common_init();
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
                tap_unicode_glyph(translator(is_shifted, keycode));
            }
            return false;
        } else if (keycode == KC_SPACE) {
            if (record->event.pressed) {
                tap_unicode_glyph(translator(is_shifted, keycode));
            }
            return false;
        }
    }
    return process_record_keymap(keycode, record);
}

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
    return process_record_keymap(keycode, record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(LAYER_LOWER);
            } else {
                layer_off(LAYER_LOWER);
            }
            return false;

        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(LAYER_RAISE);
            } else {
                layer_off(LAYER_RAISE);
            }
            return false;

        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(LAYER_ADJUST);
            } else {
                layer_off(LAYER_ADJUST);
            }
            return false;

        case KC_NOMODE:
            if (record->event.pressed) {
                if (repeat_mode != KC_NOMODE) {
                    dprint("Disabling repeat mode\n");
                }
                repeat_mode = keycode;
            }
            return false;

        case KC_REGIONAL:
            if (record->event.pressed) {
                if (repeat_mode != KC_REGIONAL) {
                    dprint("Enabling regional mode\n");
                }
                repeat_mode = keycode;
            }
            return false;

        case KC_AUSSIE:
            if (record->event.pressed) {
                if (repeat_mode != KC_AUSSIE) {
                    dprint("Enabling aussie mode\n");
                }
                repeat_mode = keycode;
            }
            return false;
    }

    if (repeat_mode == KC_REGIONAL) {
        if (((KC_A <= keycode) && (keycode <= KC_0)) || keycode == KC_SPACE) {
            if(!process_record_glyph_replacement(keycode, record, unicode_range_translator_regional)) {
                tap_unicode_glyph_nomods(0x200C);
                return false;
            }
        }
    } else if (repeat_mode == KC_AUSSIE) {
        return process_record_aussie(keycode, record);
    }

    return process_record_keymap(keycode, record);
}
