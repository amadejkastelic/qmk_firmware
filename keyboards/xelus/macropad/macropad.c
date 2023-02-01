/* Copyright 2023 Harrison Chan (Xelus)
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

#include <qp.h>
#include "kris.qgf.h"

painter_device_t qp_display;
painter_image_handle_t my_image;

void keyboard_post_init_kb(void) {
    qp_display = qp_ili9341_make_spi_device(240, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 8, 0);
    qp_init(qp_display, QP_ROTATION_0);
    qp_rect(qp_display, 0, 0, 239, 319, 0, 255, 255, true);

    my_image = qp_load_image_mem(gfx_kris);
    if (my_image != NULL) {
        qp_drawimage(qp_display, (239 - my_image->width), (319 - my_image->height), my_image);
    }

    for (int i = 0; i < 320; ++i) {
        for (int j = 0; j < 2; ++j) {
            qp_setpixel(qp_display, j, i, i, 255, 255);
        }
    }
}

// void housekeeping_task_user(void) {
//     static uint32_t last_draw = 0;
//     if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
//         last_draw = timer_read32();
//         // Draw a 240px high vertical rainbow line on X=0:
//         for (int i = 0; i < 320; ++i) {
//             for (int j = 0; j < 2; ++j) {
//                 qp_setpixel(qp_display, j, i, i, 255, 255);
//             }
//         }
//         //qp_flush(qp_display);
//     }
// }
