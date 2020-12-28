/* Copyright 2020 Harrison Chan (Xelus)
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5845 // "XE"
#define PRODUCT_ID      0x4859 // "HY"
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Xelus Hysteria

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* key matrix pins */
#define MATRIX_ROW_PINS { F5, F4, F1, F0, E6 }
#define MATRIX_COL_PINS { B4, D7, D6, D4, D5, D3, D2, D1, D0, F6, F7, C7, C6, B6 }
#define UNUSED_PINS

/* RGB Underglow */
#define RGB_DI_PIN B0
#define RGBLED_NUM 24
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 210

//#define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 4, 5, 21, 6, 7, 22, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 23, 18, 19, 20}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4