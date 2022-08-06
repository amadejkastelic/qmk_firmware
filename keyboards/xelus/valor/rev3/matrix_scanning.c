static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    /* Drive row pin low. */
    writePinLow(row_pins[current_row]);
    while (readPin(row_pins[current_row]) != 0)
        ;
    
    uint16_t porte = palReadPort(GPIOE);
    uint16_t portf = palReadPort(GPIOF);
    uint16_t portb = palReadPort(GPIOB);
    uint16_t portd = palReadPort(GPIOD);

    /* Drive row pin high again. */
    writePinHigh(row_pins[current_row]);

    matrix_row_t cols = ~(
                          ((porte & (0x1 <<  6)) >>  6) // E6
                        | ((portf & (0x1 <<  0)) <<  1) // F0
                        | ((portf & (0x1 <<  1)) <<  1) // F1
                        | ((portf & (0x1 <<  4)) >>  1) // F4
                        | ((portf & (0x1 <<  5)) >>  1) // F5
                        | ((portf & (0x1 <<  6)) >>  1) // F6
                        | ((portf & (0x1 <<  7)) >>  1) // F7
                        | ((portb & (0x1 <<  5)) <<  2) // B5
                        | ((portb & (0x1 <<  4)) <<  4) // B4
                        | ((portd & (0x1 <<  7)) <<  2) // D7
                        | ((portd & (0x1 <<  6)) <<  4) // D6
                        | ((portd & (0x1 <<  4)) <<  7) // D4
                        | ((portd & (0x1 <<  5)) <<  7) // D5
                        | ((portd & (0x1 <<  3)) <<  10) // D3
                        | ((portd & (0x1 <<  2)) <<  12) // D2
                         );
    current_matrix[current_row] = cols;

    /* Wait until col pins are high again or 'timer' expired. */
    // Taken from karlk90/yaemk
    size_t counter = 0xFF;
    while (
        ((palReadGroup(GPIOE, 0b0000000001000000, 0) != 0b0000000001000000)
        || ((palReadGroup(GPIOF, 0b0000000011110011, 0) != 0b0000000011110011)
        || ((palReadGroup(GPIOB, 0b0000000000110000, 0) != 0b0000000000110000)
        || ((palReadGroup(GPIOD, 0b0000000011111100, 0) != 0b0000000011111100)
        )) && counter != 0) {
        counter--;
    }
}