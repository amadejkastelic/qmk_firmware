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

#include <quantum.h>
#include <i2c_master.h>
#include <led_tables.h>
#include "drivers/led/issi/is31fl3731.h"
#include "ws2812.h"
#include "rev2_qmk.h"

#ifdef RGB_MATRIX_ENABLE
#include <rgb_matrix.h>
LED_TYPE rgb_matrix_ws2812_array[WS2812_LED_TOTAL];

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_1,  C3_1,  C4_1},  // LA0
    {0, C1_1,  C3_2, C4_2},   // LA1
    {0, C1_2,  C2_2, C4_3},   // LA2
    {0, C1_3,  C2_3, C3_3},   // LA3
    {0, C1_4,  C2_4, C3_4},   // LA4
    {0, C1_5,  C2_5, C3_5},   // LA5
    {0, C1_6,  C2_6, C3_6},   // LA6
    {0, C1_7,  C2_7, C3_7},   // LA7
    {0, C1_8,  C2_8, C3_8},   // LA8
    {0, C9_1,  C8_1, C7_1},   // LA9
    {0, C9_2,  C8_2, C7_2},   // LA10
    {0, C9_3,  C8_3, C7_3},   // LA11
    {0, C9_4,  C8_4, C7_4},   // LA12
    {0, C9_5,  C8_5, C7_5},   // LA13
    {0, C9_6,  C8_6, C7_6},   // LA14
    {0, C9_7,  C8_7, C6_6},   // LA15
    {0, C9_8,  C7_7, C6_7},   // LA16
    {0, C8_8,  C7_8, C6_8},   // LA17

    {0, C2_9,  C3_9,  C4_9},  // LB0
    {0, C1_9,  C3_10, C4_10}, // LB1
    {0, C1_10, C2_10, C4_11}, // LB2
    {0, C1_11, C2_11, C3_11}, // LB3
    {0, C1_12, C2_12, C3_12}, // LB4
    {0, C1_13, C2_13, C3_13}, // LB5
    {0, C1_14, C2_14, C3_14}, // LB6
    {0, C1_15, C2_15, C3_15}, // LB7
    {0, C1_16, C2_16, C3_16}, // LB8
    {0, C9_9,  C8_9,  C7_9},  // LB9
    {0, C9_10, C8_10, C7_10}, // LB10
    {0, C9_11, C8_11, C7_11}, // LB11
    {0, C9_12, C8_12, C7_12}, // LB12
    {0, C9_13, C8_13, C7_13}, // LB13
    {0, C9_14, C8_14, C7_14}, // LB14
    {0, C9_15, C8_15, C6_14}, // LB15
    {0, C9_16, C7_15, C6_15}, // LB16
    {0, C8_16, C7_16, C6_16}, // LB17

    {1, C2_1,  C3_1,  C4_1},  // LC0
    {1, C1_1,  C3_2, C4_2},   // LC1
    {1, C1_2,  C2_2, C4_3},   // LC2
    {1, C1_3,  C2_3, C3_3},   // LC3
    {1, C1_4,  C2_4, C3_4},   // LC4
    {1, C1_5,  C2_5, C3_5},   // LC5
    {1, C1_6,  C2_6, C3_6},   // LC6
    {1, C1_7,  C2_7, C3_7},   // LC7
    {1, C1_8,  C2_8, C3_8},   // LC8
    {1, C9_1,  C8_1,  C7_1},  // LC9
    {1, C9_2,  C8_2, C7_2},   // LC10
    {1, C9_3,  C8_3, C7_3},   // LC11
    {1, C9_4,  C8_4, C7_4},   // LC12
    {1, C9_5,  C8_5, C7_5},   // LC13
    {1, C9_6,  C8_6, C7_6},   // LC14
    {1, C9_7,  C8_7, C6_6},   // LC15
    {1, C9_8,  C7_7, C6_7},   // LC16
    {1, C8_8,  C7_8, C6_8},   // LC17

    {1, C2_9,  C3_9,  C4_9},  // LD0
    {1, C1_9,  C3_10, C4_10}, // LD1
    {1, C1_10, C2_10, C4_11}, // LD2
    {1, C1_11, C2_11, C3_11}, // LD3
    {1, C1_12, C2_12, C3_12}, // LD4
    {1, C1_13, C2_13, C3_13}, // LD5
    {1, C1_14, C2_14, C3_14}, // LD6
    {1, C1_15, C2_15, C3_15}, // LD7
    {1, C1_16, C2_16, C3_16}, // LD8
    {1, C9_9,  C8_9,  C7_9},  // LD9
    {1, C9_10, C8_10, C7_10}, // LD10
    {1, C9_11, C8_11, C7_11}, // LD11
    {1, C9_12, C8_12, C7_12}, // LD12
    {1, C9_13, C8_13, C7_13}, // LD13
    {1, C9_14, C8_14, C7_14}, // LD14
    {1, C9_15, C8_15, C6_14}, // LD15
    {1, C9_16, C7_15, C6_15}, // LD16
    {1, C8_16, C7_16, C6_16}, // LD17

    //fake underglows 1- 20
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0},
    {2, 0, 0, 0}
};

__attribute__ ((weak))
led_config_t g_led_config = { {
    {  0+16,  0+15,  0+14,  0+13,  0+12,  0+11,  0+10,  0+9 , 18+0 , 18+1 , 18+2 , 18+3 , 18+4 , 18+5 },
    {  0+7 ,  0+6 ,  0+5 ,  0+4 ,  0+3 ,  0+2 ,  0 +1, 18+9 , 18+10, 18+11, 18+12, 18+13, 18+14, 18+15},
    {  0+8 , 36+14, 36+13, 36+12, 36+11, 36+10, 36+9 , 54+1 , 54+2 , 54+3 , 54+4 , 54+5 , 18+8 , 18+7 },
    { 36+15, 36+5 , 36+4 , 36+3 , 36+2 , 36+1 , 54+9 , 54+10, 54+11, 54+12,NO_LED, 54+6 , 54+7 , 18+16},
    { 36+16, 36+8 , 36+7 ,NO_LED,NO_LED, 36+6 ,NO_LED,NO_LED,NO_LED, 54+13, 54+14, 54+15, 54+16, 54+8 }
}, {

    // LA0..LA17
    {255,255}, {104, 16}, {88 , 16}, {72 , 16}, {56 , 16}, {40 , 16}, {24 , 16}, {4  , 16}, {6  , 32},
    {112,  0}, {96 ,  0}, {80 ,  0}, {64 ,  0}, {48 ,  0}, {32 ,  0}, {16 ,  0}, {0  ,  0}, {255,255},
    // LB0..LB17
    {128,  0}, {144,  0}, {160,  0}, {176,  0}, {192,  0}, {208,  0}, {216,  0}, {224,  0}, {214, 32},
    {120, 16}, {136, 16}, {152, 16}, {168, 16}, {184, 16}, {200, 16}, {220, 16}, {224, 48}, {208, 48},
    // LC0..LC17
    {108, 64}, {100, 48}, {84 , 48}, {68 , 48}, {52 , 48}, {36 , 48}, {102, 64}, {42 , 64}, {22 , 64},
    {108, 32}, {92 , 32}, {76 , 32}, {60 , 32}, {44 , 32}, {28 , 32}, {10 , 48}, {2  , 64}, {255,255},
    // LD0..LD17
    {186, 48}, {124, 32}, {140, 32}, {156, 32}, {172, 32}, {188, 32}, {180, 48}, {202, 48}, {224, 64},
    {116, 48}, {132, 48}, {148, 48}, {164, 48}, {160, 64}, {176, 64}, {192, 64}, {208, 64}, {200, 64},

    //RGB UNDERGLOW
    {27 , 3}, {64 , 3}, {100, 3}, {137, 3}, {173, 3}, {209, 3}, {242, 4}, {255, 8}, {255,32}, {255,64},
    {241,64}, {212,64}, {173,64}, {137,64}, {100,64}, {63 ,64}, {28 ,64}, {0  ,64}, {0  ,32}, {0  , 8} //20
}, {
    4, 4, 4, 4, 4, 4, 4, 1, 1,  //LA0..LA8
    4, 4, 4, 4, 4, 4, 4, 1, 4,  //LA9..LA17
    4, 4, 4, 4, 4, 4, 1, 1, 1,  //LB0..LB8
    4, 4, 4, 4, 4, 4, 4, 1, 1,  //LB9..LB17
    4, 4, 4, 4, 4, 4, 4, 1, 1,  //LC0..LC8
    4, 4, 4, 4, 4, 4, 1, 1, 4,  //LC9..LC17
    1, 4, 4, 4, 4, 4, 4, 1, 1,  //LD0..LD8
    4, 4, 4, 4, 1, 1, 1, 1, 1,  //LD9..LD17

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };

//Custom Driver
static void init(void) {
    i2c_init();
    IS31FL3731_init(DRIVER_ADDR_1);
    IS31FL3731_init(DRIVER_ADDR_2);

    for (int index = 0; index < ISSI_DRIVER_TOTAL; index++) {
        bool enabled = !( ( index == 0+0 ) ||
                          ( index == 0+17 ) ||
                          ( index == 36+17 ));
        IS31FL3731_set_led_control_register(index, enabled, enabled, enabled);
    }
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_1, 0);
    IS31FL3731_update_led_control_registers(DRIVER_ADDR_2, 1);

    //RGB Underglow ws2812

}

static void flush(void) {
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_1, 0);
    IS31FL3731_update_pwm_buffers(DRIVER_ADDR_2, 1);
    ws2812_setleds(rgb_matrix_ws2812_array, WS2812_LED_TOTAL);
}

static void set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < ISSI_DRIVER_TOTAL) {
        IS31FL3731_set_color(index, red, green, blue);
    } else {
        rgb_matrix_ws2812_array[index - ISSI_DRIVER_TOTAL].r = red;
        rgb_matrix_ws2812_array[index - ISSI_DRIVER_TOTAL].g = green;
        rgb_matrix_ws2812_array[index - ISSI_DRIVER_TOTAL].b = blue;
    }
}

static void set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    IS31FL3731_set_color_all( red, green, blue );
    for (uint8_t i = 0; i < WS2812_LED_TOTAL; i++) {
        rgb_matrix_ws2812_array[i].r = red;
        rgb_matrix_ws2812_array[i].g = green;
        rgb_matrix_ws2812_array[i].b = blue;
    }
}


const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = set_color,
    .set_color_all = set_color_all
};

#endif

// void keyboard_post_init_user(void) {
//     wait_ms(5000);
//   Customise these values to desired behaviour
//   debug_enable=true;
//   debug_matrix=true;
//   debug_keyboard=true;
//   debug_mouse=true;
// }

