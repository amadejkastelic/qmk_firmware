# List of all the board related files.
BOARDSRC = ${CHIBIOS_CONTRIB}/os/hal/boards/BLACKPILL_AT32F403A/board.c

# Required include directories
BOARDINC = ${CHIBIOS_CONTRIB}/os/hal/boards/BLACKPILL_AT32F403A

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
