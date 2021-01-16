/* Copyright 2015-2017 Jack Humbert
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

enum preonic_keycodes {
    ROW0COL0 = SAFE_RANGE,
    ROW0COL1,
    ROW0COL2,
    ROW0COL3,
    ROW0COL4,
    ROW0COL5,
    ROW0COL6,
    ROW0COL7,
    ROW0COL8,
    ROW0COL9,
    ROW0COL10,
    ROW0COL11,
    ROW1COL0,
    ROW1COL1,
    ROW1COL2,
    ROW1COL3,
    ROW1COL4,
    ROW1COL5,
    ROW1COL6,
    ROW1COL7,
    ROW1COL8,
    ROW1COL9,
    ROW1COL10,
    ROW1COL11,
    ROW2COL0,
    ROW2COL1,
    ROW2COL2,
    ROW2COL3,
    ROW2COL4,
    ROW2COL5,
    ROW2COL6,
    ROW2COL7,
    ROW2COL8,
    ROW2COL9,
    ROW2COL10,
    ROW2COL11,
    ROW3COL0,
    ROW3COL1,
    ROW3COL2,
    ROW3COL3,
    ROW3COL4,
    ROW3COL5,
    ROW3COL6,
    ROW3COL7,
    ROW3COL8,
    ROW3COL9,
    ROW3COL10,
    ROW3COL11,
    ROW4COL0,
    ROW4COL1,
    ROW4COL2,
    ROW4COL3,
    ROW4COL4,
    ROW4COL5,
    ROW4COL6,
    ROW4COL7,
    ROW4COL8,
    ROW4COL9,
    ROW4COL10,
    ROW4COL11,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_preonic_grid(
ROW0COL0,ROW0COL1,ROW0COL2,ROW0COL3,ROW0COL4,ROW0COL5,ROW0COL6,ROW0COL7,ROW0COL8,ROW0COL9,ROW0COL10,ROW0COL11,
ROW1COL0,ROW1COL1,ROW1COL2,ROW1COL3,ROW1COL4,ROW1COL5,ROW1COL6,ROW1COL7,ROW1COL8,ROW1COL9,ROW1COL10,ROW1COL11,
ROW2COL0,ROW2COL1,ROW2COL2,ROW2COL3,ROW2COL4,ROW2COL5,ROW2COL6,ROW2COL7,ROW2COL8,ROW2COL9,ROW2COL10,ROW2COL11,
ROW3COL0,ROW3COL1,ROW3COL2,ROW3COL3,ROW3COL4,ROW3COL5,ROW3COL6,ROW3COL7,ROW3COL8,ROW3COL9,ROW3COL10,ROW3COL11,
ROW4COL0,ROW4COL1,ROW4COL2,ROW4COL3,ROW4COL4,ROW4COL5,ROW4COL6,ROW4COL7,ROW4COL8,ROW4COL9,ROW4COL10,ROW4COL11
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ROW0COL0:
            break;
        case ROW0COL1:
            break;
        case ROW0COL2:
            break;
        case ROW0COL3:
            break;
        case ROW0COL4:
            break;
        case ROW0COL5:
            break;
        case ROW0COL6:
            break;
        case ROW0COL7:
            break;
        case ROW0COL8:
            break;
        case ROW0COL9:
            break;
        case ROW0COL10:
            break;
        case ROW0COL11:
            break;
        case ROW1COL0:
            break;
        case ROW1COL1:
            break;
        case ROW1COL2:
            break;
        case ROW1COL3:
            break;
        case ROW1COL4:
            break;
        case ROW1COL5:
            break;
        case ROW1COL6:
            break;
        case ROW1COL7:
            break;
        case ROW1COL8:
            break;
        case ROW1COL9:
            break;
        case ROW1COL10:
            break;
        case ROW1COL11:
            break;
        case ROW2COL0:
            break;
        case ROW2COL1:
            break;
        case ROW2COL2:
            break;
        case ROW2COL3:
            break;
        case ROW2COL4:
            break;
        case ROW2COL5:
            break;
        case ROW2COL6:
            break;
        case ROW2COL7:
            break;
        case ROW2COL8:
            break;
        case ROW2COL9:
            break;
        case ROW2COL10:
            break;
        case ROW2COL11:
            break;
        case ROW3COL0:
            break;
        case ROW3COL1:
            break;
        case ROW3COL2:
            break;
        case ROW3COL3:
            break;
        case ROW3COL4:
            break;
        case ROW3COL5:
            break;
        case ROW3COL6:
            break;
        case ROW3COL7:
            break;
        case ROW3COL8:
            break;
        case ROW3COL9:
            break;
        case ROW3COL10:
            break;
        case ROW3COL11:
            break;
        case ROW4COL0:
            break;
        case ROW4COL1:
            break;
        case ROW4COL2:
            break;
        case ROW4COL3:
            break;
        case ROW4COL4:
            break;
        case ROW4COL5:
            break;
        case ROW4COL6:
            break;
        case ROW4COL7:
            break;
        case ROW4COL8:
            break;
        case ROW4COL9:
            break;
        case ROW4COL10:
            break;
        case ROW4COL11:
            break;
        }
        return true;
};
