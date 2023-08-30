# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

COMMON_VPATH += $(DRIVER_PATH)/issi

# project specific files
SRC +=  drivers/led/issi/is31fl3731.c

QUANTUM_LIB_SRC += i2c_master.c

LTO_ENABLE = yes
