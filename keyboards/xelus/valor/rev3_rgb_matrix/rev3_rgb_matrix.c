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

#include "rev3_rgb_matrix.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
  { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
    {142, 64},
    {170, 64},
    {207, 64},
    {236, 64},
    {255, 62},
    {255, 53},
    {255, 42},
    {255, 30},
    {255, 19},
    {254, 12},
    {234, 11},
    {216, 11},
    {196, 11},
    {176, 7 },
    {155, 3 },
    {135, 4 },
    {115, 0 },
    {91 , 4 },
    {73 , 7 },
    {53 , 10},
    {32 , 10},
    {11 , 11},
    {3  , 12},
    {2  , 19},
    {2  , 30},
    {2  , 42},
    {2  , 53},
    {0  , 62},
    {31 , 64},
    {67 , 64},
    {87 , 64},
    {115, 64}


}, {
  // LED Index to Flag
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2
} };


void keyboard_pre_init_kb(void) {
    rgb_matrix_set_flags(LED_FLAG_MODIFIER|LED_FLAG_UNDERGLOW|LED_FLAG_KEYLIGHT);
    keyboard_pre_init_user();
}
#endif
