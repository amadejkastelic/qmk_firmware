/* Copyright 2022 Harrison Chan (Xelus)
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
#define PRODUCT_ID      0x4A47 // JG60
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Janglad60

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { A4, A5, A6, A7, A3 }
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, B9, B8, B7, B6, B5, B4, B3, A15, A14 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

//Indicator
#define LED_CAPS_LOCK_PIN A1

// Hardware Defines
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

// HSE CLK
#define STM32_HSECLK 16000000

//Force NKRO
#define FORCE_NKRO
