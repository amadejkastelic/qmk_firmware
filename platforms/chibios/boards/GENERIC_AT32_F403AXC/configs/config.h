// Copyright 2022 Harrison Chan (@Xelus22)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Value to place in RTC backup register 10 for persistent bootloader mode
#ifndef STM32_LSECLK
#    define STM32_LSECLK 32768U
#endif  // STM32_LSECLK

#ifndef STM32_HSECLK
#    define STM32_HSECLK 25000000U
#endif  // STM32_HSECLK

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif
