#pragma once
#define DIODE_DIRECTION COL2ROW

 /* #define MATRIX_COL_PINS { E6, F0, F1, F4, F5, F6, F7, B5, B4, D7, D6, D4, D5, D3, D2 } */
#undef MATRIX_COL_PINS
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (E0, 0x40, MCU_GPIO), \
      (F0, 0xf3, MCU_GPIO), \
      (B0, 0x30, MCU_GPIO), \
      (D0, 0xfc, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x40, 0x01), \
      (1, 0x01, 0x02), \
      (1, 0x02, 0x04), \
      (1, 0x10, 0x08), \
      (1, 0x20, 0x10), \
      (1, 0x40, 0x20), \
      (1, 0x80, 0x40), \
      (2, 0x20, 0x80), \
      (2, 0x10, 0x100), \
      (3, 0x80, 0x200), \
      (3, 0x40, 0x400), \
      (3, 0x10, 0x800), \
      (3, 0x20, 0x1000), \
      (3, 0x08, 0x2000), \
      (3, 0x04, 0x4000) )

 /* #define MATRIX_ROW_PINS { B1, B2, C7, C6, B6 } */
#undef MATRIX_ROW_PINS
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x46, MCU_GPIO), \
      (C0, 0xc0, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x02, 0x01), \
      (0, 0x04, 0x02), \
      (1, 0x80, 0x04), \
      (1, 0x40, 0x08), \
      (0, 0x40, 0x10) )

