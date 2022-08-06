COL2ROW_INIT = """static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
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
    \n"""

ROW2COL_INIT = """static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        setPinInputHigh(row_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(col_pins[i]);
        writePinHigh(col_pins[i]);
    }
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    /* Drive row pin low. */
    writePinLow(col_pins[current_col]);
    while (readPin(col_pins[current_col]) != 0)
        ;
    \n"""

def lines_that_start_with(string, fp):
    return [line for line in fp if line.startswith(string)]

pins_string = ""
DIODE_DIRECTION = ""

# find diode direction
with open("config.h", "r") as fp:
    for line in lines_that_start_with("#define DIODE_DIRECTION", fp):
        line = line.replace("#define DIODE_DIRECTION","")
        line = line.strip()
        DIODE_DIRECTION = line

if DIODE_DIRECTION == "":
    print("ERROR NO DIODE DIRECTION FOUND")
    exit(0)

# find row/col depending on diode direction
with open("config.h", "r") as fp:
    if DIODE_DIRECTION == "COL2ROW":
        # find the matrix_col_pins line
        for line in lines_that_start_with("#define MATRIX_COL_PINS", fp):
            line = line.replace("#define MATRIX_COL_PINS","")
            line = line.replace("{","")
            line = line.replace("}","")
            line = line.strip()
            pins_string = line
    else:
        # ROW2COL
        for line in lines_that_start_with("#define MATRIX_ROW_PINS", fp):
            line = line.replace("#define MATRIX_ROW_PINS","")
            line = line.replace("{","")
            line = line.replace("}","")
            line = line.strip()
            pins_string = line

# convert string of pins to a list
list_pins = pins_string.split(",")
for x in range(0,len(list_pins)):
    list_pins[x] = list_pins[x].strip()
# debug
print(list_pins)

# port pins
list_ports = []
for x in list_pins:
    if x[0] not in list_ports:
        list_ports.append(x[0])

# port bitfield
port_bitfield = []
# loop through each port letter
for x in list_ports:
    print(x)

    # loop through the entire list
    bitfield = ["0"] * 16
    for y in list_pins:
        if y[0] == x:
            bitfield[int(y[1:])] = "1"
    port_bitfield.append(bitfield[::-1])


# write to the matrix_scanning file
with open("matrix_scanning.c", "w") as fp:
    if DIODE_DIRECTION == "COL2ROW":
        fp.write(COL2ROW_INIT)
    else:
        fp.write(ROW2COL_INIT)

    for x in list_ports:
        string = "    uint16_t port" + x.lower() + " = palReadPort(GPIO" + x.upper() + ");\n"
        fp.write(string)

    if DIODE_DIRECTION == "COL2ROW":
        fp.write("""\n    /* Drive row pin high again. */
    writePinHigh(row_pins[current_row]);

    """)
    else:
        fp.write("""\n    /* Drive col pin high again. */
    writePinHigh(col_pins[current_col]);

    """)

    # scanning
    if DIODE_DIRECTION == "COL2ROW":
        fp.write("""matrix_row_t cols = ~(\n""")
    else:
        fp.write("""matrix_col_t rows = ~(\n""")

    for x in range(0,len(list_pins)):
        pin_port = list_pins[x][0]
        pin_number = list_pins[x][1:]
        shift_amount = int(pin_number) - x

        string = "                        "
        if x != 0:
            string += "| "
        else:
            string += "  "
        string += "((port" + pin_port.lower() + " & (0x1 << "
        if int(pin_number) <= 9:
            string += " " + pin_number
        else:
            string += pin_number
        string += ")) "
        if shift_amount >= 0:
            string += ">> "
        else:
            string += "<< "

        if shift_amount <= 9:
            string += " " + str(abs(shift_amount))
        else:
            string += str(abs(shift_amount))
        string += ") // " + list_pins[x] + "\n"

        if x == len(list_pins) - 1:
            string += "                         );"

        fp.write(string)

    fp.write("""
    current_matrix[current_row] = cols;

    /* Wait until col pins are high again or 'timer' expired. */
    // Taken from karlk90/yaemk
    size_t counter = 0xFF;
    while (\n""")

    for x in range(0,len(list_ports)):
        string = "        "
        if x != 0:
            string += "|| "
        string += "((palReadGroup(GPIO" + list_ports[x] + ", 0b" + "".join(port_bitfield[x]) + ", 0) != 0b" + "".join(port_bitfield[x]) + ")\n"
        fp.write(string)
    fp.write(
    """        )) && counter != 0) {
        counter--;
    }
}""")
