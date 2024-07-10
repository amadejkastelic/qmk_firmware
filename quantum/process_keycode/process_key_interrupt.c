/* Copyright 2024 Harrison Chan (@xelus22)
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

#include "process_key_interrupt.h"
#include <string.h>
#include "keycodes.h"
#include "keycode_config.h"
#include "action_util.h"
#include "action_layer.h"
#include "keymap_introspection.h"
#include "matrix.h"

// key interrupt up stroke buffer
typedef struct matrix_intersection_t {
    uint8_t row;
    uint8_t col;
} matrix_intersection_t;

static bool failed_to_init = false;

matrix_intersection_t *key_interrupt_unpress_buffer = NULL;

// uint16_t buffer_keyreports[10];

// matrix_intersection_t key_interrupt_unpress_buffer[key_interrupt_count_raw()];

/**
 * @brief function for querying the enabled state of key interrupt
 *
 * @return true if enabled
 * @return false if disabled
 */
bool key_interrupt_is_enabled(void) {
    return keymap_config.key_interrupt_enable;
}

/**
 * @brief Enables key interrupt and saves state to eeprom
 *
 */
void key_interrupt_enable(void) {
    keymap_config.key_interrupt_enable = true;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Disables key interrupt and saves state to eeprom
 *
 */
void key_interrupt_disable(void) {
    keymap_config.key_interrupt_enable = false;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Toggles key interrupt's status and save state to eeprom
 *
 */
void key_interrupt_toggle(void) {
    keymap_config.key_interrupt_enable = !keymap_config.key_interrupt_enable;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief function for querying the enabled state of key interrupt
 *
 * @return true if enabled
 * @return false if disabled
 */
bool key_interrupt_up_stroke_is_enabled(void) {
    return keymap_config.key_interrupt_up_stroke_enable;
}

/**
 * @brief Toggles key interrupt's status and save state to eeprom
 *
 */
void key_interrupt_up_stroke_toggle(void) {
    keymap_config.key_interrupt_up_stroke_enable = !keymap_config.key_interrupt_up_stroke_enable;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief handler for user to override whether autocorrect should process this keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Allow key interrupt
 * @return false Stop processing and escape from key interrupt
 */
__attribute__((weak)) bool process_key_interrupt_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// init key interrupt buffer
void key_interrupt_init(void) {
    key_interrupt_unpress_buffer = malloc(key_interrupt_count() * sizeof(matrix_intersection_t));
    if (key_interrupt_unpress_buffer == NULL) {
        failed_to_init = true;
    }
}

/**
 * @brief Process handler for key_interrupt feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_key_interrupt(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_KEY_INTERRUPT_ON && keycode <= QK_KEY_INTERRUPT_UP_STROKE_TOGGLE) && record->event.pressed) {
        if (keycode == QK_KEY_INTERRUPT_ON) {
            key_interrupt_enable();
        } else if (keycode == QK_KEY_INTERRUPT_OFF) {
            key_interrupt_disable();
        } else if (keycode == QK_KEY_INTERRUPT_TOGGLE) {
            key_interrupt_toggle();
        } else if (keycode == QK_KEY_INTERRUPT_UP_STROKE_TOGGLE) {
            key_interrupt_up_stroke_toggle();
        } else {
            return true;
        }

        return false;
    }

    if (!keymap_config.key_interrupt_enable) {
        return true;
    }

    // only supports basic keycodes
    if (!IS_BASIC_KEYCODE(keycode)) {
        return true;
    }

    // custom user hook
    if (!process_key_interrupt_user(keycode, record)) {
        return true;
    }

    for (int i = 0; i < key_interrupt_count(); i++) {
        const uint16_t keycode_press = key_interrupt_get_keycode_press_at_idx(i);
        const uint16_t keycode_unpress = key_interrupt_get_keycode_unpress_at_idx(i);

        if (record->event.pressed) {
            if (!failed_to_init && keycode == keycode_unpress) {
                key_interrupt_unpress_buffer[i].row = record->event.key.row;
                key_interrupt_unpress_buffer[i].col = record->event.key.col;
            }

            if(keycode == keycode_press) {
                del_key(keycode_unpress);
            }
        }
        else
        {
            // key upstroke
            if (!failed_to_init && keycode == keycode_press) {
                uint16_t keycode_recover = keycode_at_keymap_location(get_highest_layer(layer_state | default_layer_state),
                                                                      key_interrupt_unpress_buffer[i].row,
                                                                      key_interrupt_unpress_buffer[i].col);
                if (keycode_recover == keycode_unpress && matrix_is_on(key_interrupt_unpress_buffer[i].row, key_interrupt_unpress_buffer[i].col)) {
                    add_key(keycode_unpress);
                }
            }

        }
    }

    return true;
}
