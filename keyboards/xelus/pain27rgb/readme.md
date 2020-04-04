Pain27RGB
====

This is a 60% PCB with per-key RGB LEDs and supports ANSI, ISO, winkey/winkeyless bottom row, HHKB-layout (split right shift and backspace).

Keyboard Maintainer: [Xelus](https://github.com/Xelus22)  
Hardware Supported: Pain27RGB
Hardware Availability: GroupBuy

Make example for this keyboard (after setting up your build environment):

    make xelus/pain27rgb:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


RGB Backlight Configuration
====

A keymap (in the keymaps directory) can optionally configure which RGB backlight LEDs are used, depending on the needs of the layout, by adding a config.h file in the keymap's directory.  
The following #define symbols will enable/disable a feature using 1 or 0.

    RGB_BACKLIGHT_USE_SPLIT_BACKSPACE

Split backspace is being used, enables the right LED of the split backspace (the top-right corner)

    RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT

Split left shift is being used (i.e. ISO layout), enables the right LED of the split left shift (the ISO key)

    RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT

Split right shift is being used (i.e. HHKB style layouts), enables the right LED of the split right shift (the Fn key)

    RGB_BACKLIGHT_USE_7U_SPACEBAR

A 7U spacebar is being used, controls the LEDs under the right stabilizer (of 7U spacebar) and right Alt (if 6.25U spacebar).

    RGB_BACKLIGHT_USE_ISO_ENTER

An ISO Enter is being used. Only used to tweak the location of the LED being used under ANSI Enter/backslash

    RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS

Disables the LEDs under HHKB corner blockers, useful for transparent cases.
