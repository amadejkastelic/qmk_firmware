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

// USB Device descriptor parameter
#define VENDOR_ID       0x5845 // XE
#define PRODUCT_ID      0x544A // TJ
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         TJG Macropad

// key matrix size
#define MATRIX_ROWS 3
#define MATRIX_COLS 5

//underglow
#define DIRECT_PINS { \
    { F5, F1, B1, D0, B5 }, \
    { F6, F4, B2, D2, B4 }, \
    { NO_PIN, F7, C7, NO_PIN, NO_PIN }  \
}
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// Encoder defines
#define ENCODERS_PAD_A { B6 }
#define ENCODERS_PAD_B { C6 }

// RGB Matrix defines
#define DRIVER_ADDR_1 0x74

#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 11
#define ISSI_DRIVER_TOTAL DRIVER_1_LED_TOTAL
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#define RGB_MATRIX_STARTUP_VAL 80
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

#define LAYER_STATE_8BIT
