/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xA4, 0xA6, 0x2E, 0x2A, 0x71, 0x13, 0x17, 0x35}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

#define VIAL_ENCODER_DEFAULT { KC_VOLU, KC_VOLD, KC_TRNS, KC_TRNS, KC_VOLU, KC_VOLD, KC_TRNS, KC_TRNS }

/* Total size of the EEPROM storage in bytes */
// #define TRANSIENT_EEPROM_SIZE 1024 // Not required with EEPROM emulation

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON // Sets the default mode, if none has been set
// #define RGB_MATRIX_STARTUP_HUE 0 // Sets the default hue value, if none has been set
// #define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set
// #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
// #define RGB_MATRIX_STARTUP_SPD 127 // Sets the default animation speed, if none has been set