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

#include "hysteria.h"

// Capslock Indicator 7th in WS2812 chain   - 21
// ESC Indicator 10th in WS2812 chain       - 22
// Enter Indicator 21st in WS2812 chain     - 23

// void keyboard_post_init_user(void) {
//     rgblight_set_clipping_range(0, 22);
// }

// bool led_update_kb(led_t led_state) {
//     bool res = led_update_user(led_state);
//     if(res) {

//     }

//     return res;
// }
