# MCU name
MCU = STM32F411

# Bootloader selection
BOOTLOADER = stm32-dfu

EEPROM_DRIVER = i2c

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360

ENCODER_ENABLE = yes

# save hid interface
KEYBOARD_SHARED_EP = yes

LTO_ENABLE = yes
OPT = 2

# CFLAGS += -fvect-cost-model=very-cheap
