# MCU name
MCU = STM32F411
BOARD = GENERIC_STM32_F411XE

# Bootloader selection
BOOTLOADER = stm32-dfu

EEPROM_DRIVER = i2c

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360

ENCODER_ENABLE = yes

# save hid interface
KEYBOARD_SHARED_EP = yes

DEBOUNCE_TYPE =  asym_eager_defer_pk

LTO_ENABLE = yes
OPT = 3

SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

# CFLAGS += -fvect-cost-model=very-cheap
