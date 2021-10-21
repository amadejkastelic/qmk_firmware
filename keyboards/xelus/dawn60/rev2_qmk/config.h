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
#define I2C1_TIMINGR_SCLH   41U
#define I2C1_TIMINGR_SCLL   145U

// I2C EEPROM Chip
#define EEPROM_I2C_24LC256

// Dynamic Keymap
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  65535

// // PWM RGB Underglow Defines
// #define WS2812_PWM_DRIVER PWMD3
// #define WS2812_PWM_CHANNEL 2
// #define WS2812_PWM_PAL_MODE 1
// #define WS2812_DMA_STREAM STM32_DMA1_STREAM3
// #define WS2812_DMA_CHANNEL 3
// #define WS2812_EXTERNAL_PULLUP

// SPI RGB Underglow Defines
#define WS2812_SPI SPID3 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 6 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
#define WS2812_EXTERNAL_PULLUP
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 200
//#define WS2812_SPI_SYNC
#define NOP_FUDGE 0.4

//RGB Underglow defines
#define RGB_DI_PIN B5
#define WS2812_LED_TOTAL 20

//RGB Matrix defines
#define DRIVER_ADDR_1 0x74
#define DRIVER_ADDR_2 0x76

// IS31FL3731 driver
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define ISSI_DRIVER_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL + WS2812_LED_TOTAL)

#define RGB_MATRIX_STARTUP_VAL 40
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_test_mode

#define DEBUG_MATRIX_SCAN_RATE
#define FORCE_NKRO

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4
#define MOUSEKEY_INTERVAL 1
