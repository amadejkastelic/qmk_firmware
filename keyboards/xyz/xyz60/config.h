/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x16D0
#define PRODUCT_ID      0x106D
#define DEVICE_VER      0x0001
#define MANUFACTURER    xyz
#define PRODUCT         xyz60
#define DESCRIPTION     xyz

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                         0    1    2    3    4     5   6   7    8     9   A   B  C   D   E  
#define MATRIX_ROW_PINS { B7, B9, B12, B14, B15 }
#define MATRIX_COL_PINS { B13, B8, B11, B10, B2, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

#define VIAL_KEYBOARD_UID {0x36, 0xCD, 0x23, 0xE1, 0xB4, 0x0F, 0xC3, 0xE4}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

#define USB_POLLING_INTERVAL_MS 1

#define GRAVE_ESC_CTRL_OVERRIDE
