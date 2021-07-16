/* Copyright 2021 Harrison Chan (Xelus)
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

#include "quantum.h"

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(uint8_t col);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void) {
  unselect_cols();
  init_rows();

  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);

    uint8_t rows = read_rows(col);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        if (debouncing) {
            dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
        }
        debouncing = DEBOUNCE;
      }
    }
    unselect_cols();
  }

  if (debouncing) {
    if (--debouncing) {
      _delay_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }

  matrix_scan_quantum();
  return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

/* Row pin configuration - diode connected
 * row: 0    1    2    3    4    5
 * pin: B3   A15  A14  A9   C15  C14
 *
 *
 */
static void init_rows(void) {
    DDRD  &= ~0b00101111;
    PORTD &= ~0b00101111;

    DDRB  &= ~0b10000000;
    PORTB &= ~0b10000000;

    DDRE  &= ~0b00000100;
    PORTE |=  0b00000100;
}

static uint8_t read_rows(uint8_t col) {

    return (PIND&(1<<0) ? (1<<0) : 0)  |
            (PIND&(1<<1) ? (1<<1) : 0) |
            (PIND&(1<<2) ? (1<<2) : 0) |
            (PIND&(1<<3) ? (1<<3) : 0) |
            (PIND&(1<<5) ? (1<<4) : 0) |
            (PINB&(1<<7) ? (1<<5) : 0) |
            (col== 17 ? ((PINE&(1<<2) ? 0 : (1<<1))) : 0);

}

/* Columns 0 - 16
 *
 * col 0: B1
 * col 1: B0
 * col 2: A7
 *
 * These columns uses two 74HC237D 3 to 8 bit demultiplexers.
 *               EN   A0   A1   A2
 * col / pin:    PA3  PA6  PA5  PA4  Pin
 * 3:             1    0    0    0   Y0
 * 4:             1    1    0    0   Y1
 * 5:             1    0    1    0   Y2
 * 6:             1    1    1    0   Y3
 * 7:             1    0    0    1   Y4
 * 8:             1    1    0    1   Y5
 * 9:             1    0    1    1   Y6
 * 10:            1    1    1    1   Y7
 *
 * col 11: A2
 * col 12: A1
 * col 13: A0
 * col 14: A10
 * col 15: B5
 * col 16: B4
 *
 */
static void unselect_cols(void) {
  DDRB  |=  0b01100000;
  PORTB &= ~0b01100000;

  DDRC  |=  0b11000000;
  PORTC &= ~0b11000000;

  DDRF  |=  0b00000011;
  PORTF &= ~0b00000011;
}

static void select_col(uint8_t col) {

   switch (col) {
        case 0:
            PORTC |= 0b01000000;
            break;
        case 1:
            PORTC |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 2:
            PORTC |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 3:
            PORTC |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 4:
            PORTC |= 0b11000000;
            break;
        case 5:
            PORTC |= 0b11000000;
            PORTF |= 0b00000001;
            break;
        case 6:
            PORTC |= 0b11000000;
            PORTF |= 0b00000010;
            break;
        case 7:
            PORTC |= 0b11000000;
            PORTF |= 0b00000011;
            break;
        case 8:
            PORTB |= 0b01000000;
            break;
        case 9:
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            break;
        case 10:
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            break;
        case 11:
            PORTB |= 0b01000000;
            PORTF |= 0b00000011;
            break;
        case 12:
            PORTB |= 0b01000000;
            PORTC |= 0b10000000;
            break;
        case 13:
            PORTB |= 0b01000000;
            PORTF |= 0b00000001;
            PORTC |= 0b10000000;
            break;
        case 14:
            PORTB |= 0b01000000;
            PORTF |= 0b00000010;
            PORTC |= 0b10000000;
            break;
        case 15:
            PORTB |= 0b01000000;
            PORTF |= 0b00000011;
            PORTC |= 0b10000000;
            break;
        case 16:
            PORTB |= 0b00100000;
            break;
    }
}
