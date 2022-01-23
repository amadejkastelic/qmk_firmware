// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#include "process_autocorrect.h"
#include <string.h>
#include "keycode_config.h"

#if __has_include("autocorrect_data.h")
#    include "autocorrect_data.h"
#else
#    pragma message "Warning! Autocorrect is using the default library!"
#    include "autocorrect_data_default.h"
#endif

/**
 * @brief Process handler for autocorrect feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */

bool process_autocorrect(uint16_t keycode, keyrecord_t* record) {
    static uint8_t typo_buffer[AUTOCORRECT_MAX_LENGTH] = {KC_SPC};
    static uint8_t typo_buffer_size                    = 1;

    if (keycode == AUTOCRT) {
        if (record->event.pressed) {
            typo_buffer_size = 0;
            keymap_config.autocorrect_enable ^= 1;
            eeconfig_update_keymap(keymap_config.raw);
        }
        return false;
    }

    if (!keymap_config.autocorrect_enable) {
        typo_buffer_size = 0;
        return true;
    }

    switch (keycode) {
        case KC_LSFT:
        case KC_RSFT:
            return true;
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (((keycode >> 8) & 0xF) == MOD_LSFT && !record->tap.count) {
                return true;
            }
            // fall through intentionally
#    ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#    endif
            if (record->event.pressed || !record->tap.count) {
                return true;
            }
            keycode &= 0xFF;
            break;
#endif
#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (keycode >= 0x56F0 || record->event.pressed || !record->tap.count) {
                return true;
            }
            keycode &= 0xFF;
            break;
#endif
#ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            if ((keycode & 0xF) == MOD_LSFT) {
                return true;
            }
            // fall through intentionally
#endif
        default:
            // Disable autocorrect while a mod other than shift is active.
            if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
                typo_buffer_size = 0;
                return true;
            }
            if (!record->event.pressed) {
                return true;
            }
    }

    // Subtract buffer for Backspace key, reset for other non-alpha.
    if (!(KC_A <= keycode && keycode <= KC_Z)) {
        if (keycode == KC_BSPC) {
            // Remove last character from the buffer.
            if (typo_buffer_size > 0) {
                --typo_buffer_size;
            }
            return true;
        } else if (KC_1 <= keycode && keycode <= KC_SLSH && keycode != KC_ESC) {
            // Set a word boundary if space, period, digit, etc. is pressed.
            // Behave more conservatively for the enter key. Reset, so that enter
            // can't be used on a word ending.
            if (keycode == KC_ENT || (keycode == KC_MINUS && (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
                typo_buffer_size = 0;
            }
            keycode = KC_SPC;
        } else {
            // Clear state if some other non-alpha key is pressed.
            typo_buffer_size = 0;
            return true;
        }
    }

    // Rotate oldest character if buffer is full.
    if (typo_buffer_size >= AUTOCORRECT_MAX_LENGTH) {
        memmove(typo_buffer, typo_buffer + 1, AUTOCORRECT_MAX_LENGTH - 1);
        typo_buffer_size = AUTOCORRECT_MAX_LENGTH - 1;
    }

    // Append `keycode` to buffer.
    typo_buffer[typo_buffer_size++] = keycode;
    // Return if buffer is smaller than the shortest word.
    if (typo_buffer_size < AUTOCORRECT_MIN_LENGTH) {
        return true;
    }

    // Check for typo in buffer using a trie stored in `autocorrect_data`.
    uint16_t state = 0;
    uint8_t  code  = pgm_read_byte(autocorrect_data + state);
    for (uint8_t i = typo_buffer_size - 1; i >= 0; --i) {
        uint8_t const key_i = typo_buffer[i];

        if (code & 64) {  // Check for match in node with multiple children.
            code &= 63;
            for (; code != key_i; code = pgm_read_byte(autocorrect_data + (state += 3))) {
                if (!code) return true;
            }
            // Follow link to child node.
            state = (pgm_read_byte(autocorrect_data + state + 1) | pgm_read_byte(autocorrect_data + state + 2) << 8);
            // Check for match in node with single child.
        } else if (code != key_i) {
            return true;
        } else if (!(code = pgm_read_byte(autocorrect_data + (++state)))) {
            ++state;
        }

        code = pgm_read_byte(autocorrect_data + state);

        if (code & 128) {  // A typo was found! Apply autocorrect.
            const uint8_t backspaces = code & 63;
            for (uint8_t i = 0; i < backspaces; ++i) {
                tap_code(KC_BSPC);
            }
            send_string_P((char const*)(autocorrect_data + state + 1));

            if (keycode == KC_SPC) {
                typo_buffer[0]   = KC_SPC;
                typo_buffer_size = 1;
                return true;
            } else {
                typo_buffer_size = 0;
                return false;
            }
        }
    }
    return true;
}
