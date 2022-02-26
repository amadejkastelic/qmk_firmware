# MCU name
MCU = STM32L422

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

EEPROM_DRIVER = i2c

CUSTOM_MATRIX = yes
SRC += matrix.c

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = custom

COMMON_VPATH += $(DRIVER_PATH)/issi
SRC += drivers/led/issi/is31fl3741.c

# LTO_ENABLE = yes
# OPT = 2

# DEBOUNCE_TYPE = sym_defer_pk
