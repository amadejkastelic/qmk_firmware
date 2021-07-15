/* Copyright 2017 Jason Williams (Wilba)
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

#include "tjg.h"

// tested and working
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_1,   C3_2,   C4_2}, //A1
    {0, C1_2,   C2_2,   C4_3}, //A2
    {0, C1_3,   C2_3,   C3_3}, //A3
    {0, C1_4,   C2_4,   C3_4}, //A4
    {0, C9_1,   C8_1,   C7_1}, //A9
    {0, C9_2,   C8_2,   C7_2}, //A10
    {0, C9_3,   C8_3,   C7_3}, //A11
    {0, C9_4,   C8_4,   C7_4}, //A12
    {0, C9_5,   C8_5,   C7_5}, //A13
    {0, C9_6,   C8_6,   C7_6}, //A14
    {0, C9_7,   C8_7,   C6_6}  //A15
};

__attribute__ ((weak))
led_config_t g_led_config = { {
    { 0, 1, 2, 3, NO_LED },
    { 4, 5, 6, 7, 8 },
    { NO_LED, 9, 10, NO_LED, NO_LED }
}, {
    {0  ,  0},  //A1
    {56 ,  0},  //A2
    {112,  0},  //A3
    {168,  0},  //A4
    {0  , 32},  //A9
    {56 , 32},  //A10
    {112, 32},  //A11
    {168, 32},  //A12
    {224, 32},  //A13
    {56 , 64},  //A14
    {196, 64}   //A15
}, {
    4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4
} };
#endif
