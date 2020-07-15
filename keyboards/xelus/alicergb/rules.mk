# MCU name
MCU = STM32F072
BOARD = ST_STM32F072B_DISCOVERY

# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite            # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes              # Mouse keys
EXTRAKEY_ENABLE = yes              # Audio control and System control
CONSOLE_ENABLE = no                # Console for debug
COMMAND_ENABLE = no                # Commands for debug and configuration
BACKLIGHT_ENABLE = no              # Enable keyboard backlight functionality
SLEEP_LED_ENABLE = no              # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes                  # USB Nkey Rollover
AUDIO_ENABLE = no                  # Audio output on port C6
NO_USB_STARTUP_CHECK = no          # Disable initialization only when usb is plugged in
MIDI_ENABLE = no                   # MIDI support
UNICODE_ENABLE = no                # Uni code
BLUETOOTH_ENABLE = no              # Enable Bluetooth with the Adafruit EZ-Key HID
FAUXCLICKY_ENABLE = no             # Use buzzer to emulate clicky switches
RGBLIGHT_ENABLE = spi              # Enable WS2812 RGB underlight. - We have custom RGB underglow
EEPROM_DRIVER = i2c


CIE1931_CURVE = yes

LAYOUT = LAYOUT_all

# project specific files
SRC +=	keyboards/wilba_tech/wt_main.c \
		keyboards/wilba_tech/wt_rgb_backlight.c \
		drivers/issi/is31fl3731.c \
		quantum/color.c \
		ws2812_spi.c

QUANTUM_LIB_SRC += i2c_master.c 
