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
#define PRODUCT_ID      0x0060 // Dawn60
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Dawn60Rev2

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//underglow
#define MATRIX_ROW_PINS { A9, A10, B13, B14, B15 }
#define MATRIX_COL_PINS { A8, A2, A1, A0, B11, B10, B2, B1, B0, A7, A6, A5, A4, A3 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// I2C Defines
#define I2C1_SCL            8
#define I2C1_SDA            9
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 7U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   45U
#define I2C1_TIMINGR_SCLL   149U

// I2C EEPROM Chip
#define EEPROM_I2C_24LC256

// Dynamic Keymap
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  (32768 - 1)

// WS2812 Driver Defines
#define WS2812_SPI SPID3 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 6 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
#define WS2812_SPI_SCK_PIN B3
#define WS2812_SPI_SCK_PAL_MODE 6
#define WS2812_SPI_USE_CIRCULAR_BUFFER
#define WS2812_EXTERNAL_PULLUP
// #define WS2812_SPI_SYNC
#define NOP_FUDGE 0.4

//RGB Underglow defines
#define RGB_DI_PIN B5
#define RGBLED_NUM 20
#define WS2812_LED_TOTAL RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 150

//RGB Matrix defines
#define DRIVER_ADDR_1 0x74
#define DRIVER_ADDR_2 0x76

// IS31FL3731 driver
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define ISSI_DRIVER_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL + WS2812_LED_TOTAL)

// RGB Matrix Settings
#define RGB_MATRIX_STARTUP_VAL 40
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_test_mode

#define FORCE_NKRO
#define DEBUG_EEPROM_OUTPUT

//Light Layers
#define RGBLIGHT_LAYERS
