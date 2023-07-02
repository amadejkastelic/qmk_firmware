import json
import os.path

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

# Helper Functions
def lines_that_start_with(string, fp):
    return [line for line in fp if line.startswith(string)]

def lines_containing(string, fp):
    return [line for line in fp if (string in line)]

def removeDigits(s):
    answer = []
    for char in s:
        if not char.isdigit():
            answer.append(char)
    return ''.join(answer)

def removeChars(s):
    answer = []
    for char in s:
        if char.isdigit():
            answer.append(char)
    return ''.join(answer)

# data required
pins_string = ""
DIODE_DIRECTION = ""
json_data = ""
mcu_type = ""

# load info.json
json_found = os.path.isfile("./info.json")
if json_found:
    with open("info.json", "r") as fp:
        json_data = json.load(fp)

# check MCU type
# stm32, avr or RPI
# requires info.json
mcu_type = json_data["processor"].lower()
if mcu_type == "":
    print("requires info.json to extract mcu type")
    exit(0)

if "stm32" in mcu_type:
    mcu_type = "stm32"

if "atmega32u4" in mcu_type:
    mcu_type = "avr"

if "rp2040" in mcu_type:
    mcu_type = "rp2040"

if mcu_type == "":
    print("unsupported MCU")
    exit(0)

print("mcu type:", mcu_type)

# find diode direction
if json_found and "diode_direction" in json_data.keys():
    DIODE_DIRECTION = json_data["diode_direction"]

# config.h override
check_file = os.path.isfile("./config.h")
if check_file:
    with open("config.h", "r") as fp:
        for line in lines_that_start_with("#define DIODE_DIRECTION", fp):
            line = line.replace("#define DIODE_DIRECTION","")
            line = line.strip()
            DIODE_DIRECTION = line

if DIODE_DIRECTION == "":
    # default is col2row
    DIODE_DIRECTION = "COL2ROW"

# find row/col depending on diode direction
if json_found and "diode_direction" in json_data.keys():
    if DIODE_DIRECTION == "COL2ROW":
        # find the matrix_col_pins line
        pins_string = json_data["matrix_pins"]["cols"]
    else:
        # ROW2COL
        pins_string = json_data["matrix_pins"]["rows"]
    pins_string = ",".join(pins_string)

# config.h override
if check_file:
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

if pins_string == "":
    print("error no pins found")
    exit(0)

# convert string of pins to a list
list_pins = pins_string.split(",")
for x in range(0,len(list_pins)):
    list_pins[x] = list_pins[x].replace('"',"").strip()
# debug
# print(list_pins)

# port pins
list_ports = []
for x in list_pins:
    port_string = removeDigits(x)
    if port_string not in list_ports:
        list_ports.append(port_string)
list_ports.sort()

# port bitfield
port_bitfield = []
# loop through each port letter
for letter in list_ports:
    # print(letter)

    num_bits = 0

    if mcu_type == "stm32":
        num_bits = 16
    elif mcu_type == "avr":
        num_bits = 8

    # loop through the entire list
    bitfield = ["0"] * num_bits
    for pin in list_pins:
        if removeDigits(pin) == letter:
            bitfield[int(removeChars(pin))] = "1"

    print(bitfield)
    port_bitfield.append(bitfield[::-1])

# write to the matrix_scanning file
with open("matrix_scanning.c", "w") as fp:
    fp.write('''#include "quantum.h"\n\n''')

    if DIODE_DIRECTION == "COL2ROW":
        fp.write(COL2ROW_INIT)
    else:
        fp.write(ROW2COL_INIT)

    for x in list_ports:
        string = ""
        GPIO_string = ""
        if mcu_type == "stm32":
            GPIO_string = "GPIO" + x.upper()
            string = "    uint16_t port" + x.lower() + " = palReadPort(" + GPIO_string + ");\n"
        elif mcu_type == "avr":
            GPIO_string = "PIN" + x.upper() + "_ADDRESS"
            string = "    uint8_t port" + x.lower() + " = PIN" + x.upper() + ";\n"

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

        string += "(matrix_row_t)((port" + pin_port.lower() + " & (0x1 << "

        if int(pin_number) <= 9:
            string += " "
        string += pin_number
        string += ")) "
        if shift_amount >= 0:
            string += ">> "
        else:
            string += "<< "

        if shift_amount <= 9:
            string += " "
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
    while ((\n""")

    for x in range(0,len(list_ports)):
        string = " " * 8

        if mcu_type == "stm32":
            string += "(palReadGroup(GPIO" + list_ports[x] + ", 0b" + "".join(port_bitfield[x]) + ", 0) != 0b" + "".join(port_bitfield[x]) + ")"
        elif mcu_type == "avr":
            string += "((PIN" + list_ports[x].upper() + " & 0b" + "".join(port_bitfield[x]) + ") != 0b" + "".join(port_bitfield[x]) + ")"

        if x != len(list_ports) - 1:
            string += " ||"
        string += "\n"
        fp.write(string)
    fp.write(
    """    ) && counter != 0) {
        counter--;
    }
}""")
