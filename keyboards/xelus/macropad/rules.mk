EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = rp2040_flash

ENCODER_MAP_ENABLE = yes

QUANTUM_PAINTER_DRIVERS += ili9341_spi

LTO_ENABLE = yes

SRC += kris_qgf.c
