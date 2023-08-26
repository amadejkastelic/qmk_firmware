/* Copyright 2019 Jason Williams (Wilba)
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

#pragma once

#include "eeconfig.h" // for EECONFIG_SIZE
#include "action.h"

// Keyboard level code can change where VIA stores the magic.
// The magic is the build date YYMMDD encoded as BCD in 3 bytes,
// thus installing firmware built on a different date to the one
// already installed can be detected and the EEPROM data is reset.
// The only reason this is important is in case EEPROM usage changes
// and the EEPROM was not explicitly reset by bootmagic lite.
#ifndef VIA_EEPROM_MAGIC_ADDR
#    define VIA_EEPROM_MAGIC_ADDR (EECONFIG_SIZE)
#endif

#define VIA_EEPROM_LAYOUT_OPTIONS_ADDR (VIA_EEPROM_MAGIC_ADDR + 3)

// Changing the layout options size after release will invalidate EEPROM,
// but this is something that should be set correctly on initial implementation.
// 1 byte is enough for most uses (i.e. 8 binary states, or 6 binary + 1 ternary/quaternary )
#ifndef VIA_EEPROM_LAYOUT_OPTIONS_SIZE
#    define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 1
#endif

// Allow override of the layout options default value.
// This requires advanced knowledge of how VIA stores layout options
// and is only really useful for setting a boolean layout option
// state to true by default.
#ifndef VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT
#    define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00000000
#endif

// EEPROM memory used by VIA indicators
#define VIA_EEPROM_INDICATORS_CONFIG_ADDR (VIA_EEPROM_LAYOUT_OPTIONS_ADDR + VIA_EEPROM_LAYOUT_OPTIONS_SIZE)

#ifdef VIA_INDICATORS_ENABLE
#    include "color.h
"
typedef struct PACKED {
    bool    enable_caps_lock : 1;               // |
    bool    enable_num_lock : 1;                // |
    bool    enable_scroll_lock : 1;             // |
    bool    enable_layer_1_indicator : 1;       // |
    bool    caps_lock_override_animation : 1;   // |
    bool    num_lock_override_animation : 1;    // |
    bool    scroll_lock_override_animation : 1; // |
    bool    layer_1_override_animation : 1;     // 1 byte
    HSV     caps_lock_indicator;                // 3 bytes
    HSV     num_lock_indicator;                 // 3 bytes
    HSV     scroll_lock_indicator;              // 3 bytes
    HSV     layer_1_indicator;                  // 3 bytes
    uint8_t caps_lock_key;                      // 1 byte
    uint8_t num_lock_key;                       // 1 byte
    uint8_t scroll_lock_key;                    // 1 byte
    uint8_t layer_1_indicator_key;              // 1 byte
} via_qmk_indicators_config_t;
#    define VIA_EEPROM_INDICATORS_SIZE sizeof(via_qmk_indicators_config_t)
_Static_assert(sizeof(via_qmk_indicators_config_t) == 17, "VIA INDICATORS EECONFIG out of spec.");

// extern via_qmk_indicators_config_t via_qmk_indicators_config;
#else
#    define VIA_EEPROM_INDICATORS_SIZE 0
#endif

// The end of the EEPROM memory used by VIA
// By default, dynamic keymaps will start at this if there is no
// custom config
#define VIA_EEPROM_CUSTOM_CONFIG_ADDR (VIA_EEPROM_INDICATORS_CONFIG_ADDR + VIA_EEPROM_INDICATORS_SIZE)

#ifndef VIA_EEPROM_CUSTOM_CONFIG_SIZE
#    define VIA_EEPROM_CUSTOM_CONFIG_SIZE 0
#endif

#define VIA_EEPROM_CONFIG_END (VIA_EEPROM_CUSTOM_CONFIG_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE)

// This is changed only when the command IDs change,
// so VIA Configurator can detect compatible firmware.
#define VIA_PROTOCOL_VERSION 0x000C

// This is a version number for the firmware for the keyboard.
// It can be used to ensure the VIA keyboard definition and the firmware
// have the same version, especially if there are changes to custom values.
// Define this in config.h to override and bump this number.
// This is *not* required if the keyboard is only using basic functionality
// and not using custom values for lighting, rotary encoders, etc.
#ifndef VIA_FIRMWARE_VERSION
#    define VIA_FIRMWARE_VERSION 0x00000000
#endif

enum via_command_id {
    id_get_protocol_version                 = 0x01, // always 0x01
    id_get_keyboard_value                   = 0x02,
    id_set_keyboard_value                   = 0x03,
    id_dynamic_keymap_get_keycode           = 0x04,
    id_dynamic_keymap_set_keycode           = 0x05,
    id_dynamic_keymap_reset                 = 0x06,
    id_custom_set_value                     = 0x07,
    id_custom_get_value                     = 0x08,
    id_custom_save                          = 0x09,
    id_eeprom_reset                         = 0x0A,
    id_bootloader_jump                      = 0x0B,
    id_dynamic_keymap_macro_get_count       = 0x0C,
    id_dynamic_keymap_macro_get_buffer_size = 0x0D,
    id_dynamic_keymap_macro_get_buffer      = 0x0E,
    id_dynamic_keymap_macro_set_buffer      = 0x0F,
    id_dynamic_keymap_macro_reset           = 0x10,
    id_dynamic_keymap_get_layer_count       = 0x11,
    id_dynamic_keymap_get_buffer            = 0x12,
    id_dynamic_keymap_set_buffer            = 0x13,
    id_dynamic_keymap_get_encoder           = 0x14,
    id_dynamic_keymap_set_encoder           = 0x15,
    id_unhandled                            = 0xFF,
};

enum via_keyboard_value_id {
    id_uptime              = 0x01,
    id_layout_options      = 0x02,
    id_switch_matrix_state = 0x03,
    id_firmware_version    = 0x04,
    id_device_indication   = 0x05,
};

enum via_channel_id {
    id_custom_channel         = 0,
    id_qmk_backlight_channel  = 1,
    id_qmk_rgblight_channel   = 2,
    id_qmk_rgb_matrix_channel = 3,
    id_qmk_audio_channel      = 4,
    id_qmk_led_matrix_channel = 5,
#ifdef VIA_INDICATORS_ENABLE
    id_qmk_indicators_channel = 6
#endif
};

enum via_qmk_backlight_value {
    id_qmk_backlight_brightness = 1,
    id_qmk_backlight_effect     = 2,
};

enum via_qmk_rgblight_value {
    id_qmk_rgblight_brightness   = 1,
    id_qmk_rgblight_effect       = 2,
    id_qmk_rgblight_effect_speed = 3,
    id_qmk_rgblight_color        = 4,
};

enum via_qmk_rgb_matrix_value {
    id_qmk_rgb_matrix_brightness   = 1,
    id_qmk_rgb_matrix_effect       = 2,
    id_qmk_rgb_matrix_effect_speed = 3,
    id_qmk_rgb_matrix_color        = 4,
};

enum via_qmk_led_matrix_value {
    id_qmk_led_matrix_brightness   = 1,
    id_qmk_led_matrix_effect       = 2,
    id_qmk_led_matrix_effect_speed = 3,
};

enum via_qmk_audio_value {
    id_qmk_audio_enable        = 1,
    id_qmk_audio_clicky_enable = 2,
};

#ifdef VIA_INDICATORS_ENABLE
enum via_qmk_indicator_value { id_qmk_caps_lock_enable = 1, id_qmk_caps_lock_brightness, id_qmk_caps_lock_color, id_qmk_caps_lock_key, id_qmk_caps_lock_override_animation, id_qmk_num_lock_enable, id_qmk_num_lock_brightness, id_qmk_num_lock_color, id_qmk_num_lock_key, id_qmk_num_lock_override_animation, id_qmk_scroll_lock_enable, id_qmk_scroll_lock_brightness, id_qmk_scroll_lock_color, id_qmk_scroll_lock_key, id_qmk_scroll_lock_override_animation, id_qmk_layer_1_indicator_enable, id_qmk_layer_1_indicator_brightness, id_qmk_layer_1_indicator_color, id_qmk_layer_1_indicator_key, id_qmk_layer_1_indicator_override_animation };
#endif

// Can be called in an overriding via_init_kb() to test if keyboard level code usage of
// EEPROM is invalid and use/save defaults.
bool via_eeprom_is_valid(void);

// Sets VIA/keyboard level usage of EEPROM to valid/invalid
// Keyboard level code (eg. via_init_kb()) should not call this
void via_eeprom_set_valid(bool valid);

// Called by QMK core to initialize dynamic keymaps etc.
void eeconfig_init_via(void);
void via_init(void);

// Used by VIA to store and retrieve the layout options.
uint32_t via_get_layout_options(void);
void     via_set_layout_options(uint32_t value);
void     via_set_layout_options_kb(uint32_t value);

// Used by VIA to tell a device to flash LEDs (or do something else) when that
// device becomes the active device being configured, on startup or switching
// between devices.
void via_set_device_indication(uint8_t value);

// Called by QMK core to process VIA-specific keycodes.
bool process_record_via(uint16_t keycode, keyrecord_t *record);

// These are made external so that keyboard level custom value handlers can use them.
#if defined(BACKLIGHT_ENABLE)
void via_qmk_backlight_command(uint8_t *data, uint8_t length);
void via_qmk_backlight_set_value(uint8_t *data);
void via_qmk_backlight_get_value(uint8_t *data);
void via_qmk_backlight_save(void);
#endif

#if defined(RGBLIGHT_ENABLE)
void via_qmk_rgblight_command(uint8_t *data, uint8_t length);
void via_qmk_rgblight_set_value(uint8_t *data);
void via_qmk_rgblight_get_value(uint8_t *data);
void via_qmk_rgblight_save(void);
#endif

#if defined(RGB_MATRIX_ENABLE)
void via_qmk_rgb_matrix_command(uint8_t *data, uint8_t length);
void via_qmk_rgb_matrix_set_value(uint8_t *data);
void via_qmk_rgb_matrix_get_value(uint8_t *data);
void via_qmk_rgb_matrix_save(void);
#endif

#if defined(LED_MATRIX_ENABLE)
void via_qmk_led_matrix_command(uint8_t *data, uint8_t length);
void via_qmk_led_matrix_set_value(uint8_t *data);
void via_qmk_led_matrix_get_value(uint8_t *data);
void via_qmk_led_matrix_save(void);
values_save
#endif

#if defined(AUDIO_ENABLE)
    void
     via_qmk_audio_command(uint8_t *data, uint8_t length);
void via_qmk_audio_set_value(uint8_t *data);
void via_qmk_audio_get_value(uint8_t *data);
void via_qmk_audio_save(void);
#endif

#if defined(VIA_INDICATORS_ENABLE)

// todo make max brightness RGB_MATRIX_MAXIMUM_BRIGHTNESS
// need to move from rgb_matrix.c to rgb_matrix.h
#    ifndef VIA_QMK_DEFAULT_CAPS_LOCK_HSV
#        define VIA_QMK_DEFAULT_CAPS_LOCK_HSV \
            { 0, 0, 255 }
#    endif
#    ifndef VIA_QMK_DEFAULT_NUM_LOCK_HSV
#        define VIA_QMK_DEFAULT_NUM_LOCK_HSV \
            { 60, 0, 255 }
#    endif
#    ifndef VIA_QMK_DEFAULT_SCROLL_LOCK_HSV
#        define VIA_QMK_DEFAULT_SCROLL_LOCK_HSV \
            { 120, 0, 255 }
#    endif
#    ifndef VIA_QMK_DEFAULT_LAYER_1_HSV
#        define VIA_QMK_DEFAULT_LAYER_1_HSV \
            { 180, 0, 255 }
#    endif
#    ifndef VIA_QMK_DEFAULT_CAPS_LOCK_ENABLE
#        define VIA_QMK_DEFAULT_CAPS_LOCK_ENABLE false
#    endif
#    ifndef VIA_QMK_DEFAULT_NUM_LOCK_ENABLE
#        define VIA_QMK_DEFAULT_NUM_LOCK_ENABLE false
#    endif
#    ifndef VIA_QMK_DEFAULT_SCROLL_LOCK_ENABLE
#        define VIA_QMK_DEFAULT_SCROLL_LOCK_ENABLE false
#    endif
#    ifndef VIA_QMK_DEFAULT_LAYER_1_ENABLE
#        define VIA_QMK_DEFAULT_LAYER_1_ENABLE false
#    endif
#    ifndef VIA_QMK_DEFAULT_CAPS_LOCK_KEY
#        define VIA_QMK_DEFAULT_CAPS_LOCK_KEY 0
#    endif
#    ifndef VIA_QMK_DEFAULT_NUM_LOCK_KEY
#        define VIA_QMK_DEFAULT_NUM_LOCK_KEY 0
#    endif
#    ifndef VIA_QMK_DEFAULT_SCROLL_LOCK_KEY
#        define VIA_QMK_DEFAULT_SCROLL_LOCK_KEY 0
#    endif
#    ifndef VIA_QMK_DEFAULT_LAYER_1_KEY
#        define VIA_QMK_DEFAULT_LAYER_1_KEY 0
#    endif
#    ifndef VIA_QMK_DEFAULT_CAPS_LOCK_OVERRIDE_ANIM
#        define VIA_QMK_DEFAULT_CAPS_LOCK_OVERRIDE_ANIM false
#    endif
#    ifndef VIA_QMK_DEFAULT_NUM_LOCK_OVERRIDE_ANIM
#        define VIA_QMK_DEFAULT_NUM_LOCK_OVERRIDE_ANIM false
#    endif
#    ifndef VIA_QMK_DEFAULT_SCROLL_LOCK_OVERRIDE_ANIM
#        define VIA_QMK_DEFAULT_SCROLL_LOCK_OVERRIDE_ANIM false
#    endif
#    ifndef VIA_QMK_DEFAULT_LAYER_1_OVERRIDE_ANIM
#        define VIA_QMK_DEFAULT_LAYER_1_OVERRIDE_ANIM false
#    endif

void via_qmk_indicators_command(uint8_t *data, uint8_t length);
void via_qmk_indicators_set_value(uint8_t *data);
void via_qmk_indicators_get_value(uint8_t *data);
void via_qmk_indicators_save(void);
void via_qmk_indicators_load(void);
#    if defined(RGB_MATRIX_ENABLE)
void via_qmk_rgb_matrix_indicators(void);
#    endif
#endif
