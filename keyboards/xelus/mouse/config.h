/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 2

#define USB_MAX_POWER_CONSUMPTION 100

/* disable action features */
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

// I2C eeprom
// #define EEPROM_I2C_24LC64
// BL24C04A
#define EXTERNAL_EEPROM_BYTE_COUNT      512
#define EXTERNAL_EEPROM_PAGE_SIZE       16
#define EXTERNAL_EEPROM_ADDRESS_SIZE    2
#define EXTERNAL_EEPROM_WRITE_TIME      3

// I2C config
#define I2C1_SCL            6
#define I2C1_SDA            7
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_CLOCK_SPEED    400000
#define I2C1_DUTY_CYCLE     FAST_DUTY_CYCLE_2

// SPI config
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5

// RGB
// #define RGB_DI_PIN A8
// #define RGBLED_NUM 8
// #define WS2812_EXTERNAL_PULLUP
// #define RGBLIGHT_DEFAULT_VAL 128

// RGB Animations
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #define RGBLIGHT_EFFECT_BREATHING

// default startup
// #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

// PWM config
// #define WS2812_PWM_DRIVER PWMD1
// #define WS2812_PWM_CHANNEL 1
// #define WS2812_PWM_PAL_MODE 1
// #define WS2812_DMA_STREAM STM32_DMA2_STREAM5
// #define WS2812_DMA_CHANNEL 6
// #define WS2812_DMAMUX_ID STM32_DMAMUX2_TIM1_UP

// PMW3360 config
#define PMW33XX_CS_PIN           A4
#define PMW33XX_SPI_DIVISOR      32
//#define PMW33XX_LIFTOFF_DISTANCE 0x27
#define PMW33XX_LIFTOFF_DISTANCE 0x02
#define PMW33XX_CPI              3200
#define POINTING_DEVICE_MOTION_PIN B0
//#define POINTING_DEVICE_TASK_THROTTLE_MS 1

//mouse configs
#define MOUSE_EXTENDED_REPORT

// Encoder
#define ENCODERS_PAD_A { B13 }
#define ENCODERS_PAD_B { B12 }
#define ENCODER_RESOLUTION 2

// F411 16MHz HSE
#define STM32_HSECLK 16000000
