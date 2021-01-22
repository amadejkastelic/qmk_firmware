/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum preonic_keycodes {
    ROW0COL0 = SAFE_RANGE,
    ROW0COL1,
    ROW0COL2,
    ROW0COL3,
    ROW0COL4,
    ROW0COL5,
    ROW0COL6,
    ROW0COL7,
    ROW0COL8,
    ROW0COL9,
    ROW0COL10,
    ROW0COL11,
    ROW1COL0,
    ROW1COL1,
    ROW1COL2,
    ROW1COL3,
    ROW1COL4,
    ROW1COL5,
    ROW1COL6,
    ROW1COL7,
    ROW1COL8,
    ROW1COL9,
    ROW1COL10,
    ROW1COL11,
    ROW2COL0,
    ROW2COL1,
    ROW2COL2,
    ROW2COL3,
    ROW2COL4,
    ROW2COL5,
    ROW2COL6,
    ROW2COL7,
    ROW2COL8,
    ROW2COL9,
    ROW2COL10,
    ROW2COL11,
    ROW3COL0,
    ROW3COL1,
    ROW3COL2,
    ROW3COL3,
    ROW3COL4,
    ROW3COL5,
    ROW3COL6,
    ROW3COL7,
    ROW3COL8,
    ROW3COL9,
    ROW3COL10,
    ROW3COL11,
    ROW4COL0,
    ROW4COL1,
    ROW4COL2,
    ROW4COL3,
    ROW4COL4,
    ROW4COL5,
    ROW4COL6,
    ROW4COL7,
    ROW4COL8,
    ROW4COL9,
    ROW4COL10,
    ROW4COL11,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_preonic_grid(
ROW0COL0,ROW0COL1,ROW0COL2,ROW0COL3,ROW0COL4,ROW0COL5,ROW0COL6,ROW0COL7,ROW0COL8,ROW0COL9,ROW0COL10,ROW0COL11,
ROW1COL0,ROW1COL1,ROW1COL2,ROW1COL3,ROW1COL4,ROW1COL5,ROW1COL6,ROW1COL7,ROW1COL8,ROW1COL9,ROW1COL10,ROW1COL11,
ROW2COL0,ROW2COL1,ROW2COL2,ROW2COL3,ROW2COL4,ROW2COL5,ROW2COL6,ROW2COL7,ROW2COL8,ROW2COL9,ROW2COL10,ROW2COL11,
ROW3COL0,ROW3COL1,ROW3COL2,ROW3COL3,ROW3COL4,ROW3COL5,ROW3COL6,ROW3COL7,ROW3COL8,ROW3COL9,ROW3COL10,ROW3COL11,
ROW4COL0,ROW4COL1,ROW4COL2,ROW4COL3,ROW4COL4,ROW4COL5,ROW4COL6,ROW4COL7,ROW4COL8,ROW4COL9,ROW4COL10,ROW4COL11
)
};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        key_timer = timer_read();
        switch (keycode) {
            case ROW0COL0:
                SEND_STRING(":gobbo:");
                break;
            case ROW1COL0:
                SEND_STRING(":GobboRGB~1:");
                break;
            case ROW2COL0:
                SEND_STRING(":GobboBunnings~1:");
                break;
            case ROW3COL0:
                SEND_STRING(":GobboTaeEyes:");
                break;
            case ROW4COL0:
                SEND_STRING(":GobboLaserEyes:");
                break;
            case ROW0COL1:
                SEND_STRING(":seulgi~1:");
                break;
            case ROW1COL1:
                SEND_STRING(":TzuyuSmiley:");
                break;
            case ROW2COL1:
                SEND_STRING(":aSanaShrug:");
                break;
            case ROW3COL1:
                SEND_STRING(":achaewonwow:");
                break;
            case ROW4COL1:
                SEND_STRING(":chaewonshoot:");
                break;
            case ROW0COL2:
                SEND_STRING(":wendygreasy:");
                break;
            case ROW1COL2:
                SEND_STRING(":TzuyuOk:");
                break;
            case ROW2COL2:
                SEND_STRING(":yunahappy~1:");
                break;
            case ROW3COL2:
                SEND_STRING(":yuna~1:");
                break;
            case ROW4COL2:
                SEND_STRING(":yuna~2:");
                break;
            case ROW0COL3:
                SEND_STRING(":snag:");
                break;
            case ROW1COL3:
                SEND_STRING(":FOMO:");
                break;
            case ROW2COL3:
                SEND_STRING(":wut:");
                break;
            case ROW3COL3:
                SEND_STRING(":idyllic:");
                break;
            case ROW4COL3:
                SEND_STRING(":liablep:");
                break;
            case ROW0COL4:
                SEND_STRING(":salmo:");
                break;
            case ROW1COL4:
                SEND_STRING(":wakeuprama:");
                break;
            case ROW2COL4:
                SEND_STRING(":deric:");
                break;
            case ROW3COL4:
                SEND_STRING(":dadlaugh:");
                break;
            case ROW4COL4:
                SEND_STRING(":cam:");
                break;
            case ROW0COL5:
                SEND_STRING(":migoreng:");
                break;
            case ROW1COL5:
                SEND_STRING(":zoomg:");
                break;
            case ROW2COL5:
                SEND_STRING(":laserninja:");
                break;
            case ROW3COL5:
                SEND_STRING(":yum~1:");
                break;
            case ROW4COL5:
                SEND_STRING(":kodazzle:");
                break;
            case ROW0COL6:
                SEND_STRING(":umm1:");
                break;
            case ROW1COL6:
                SEND_STRING(":PepeHands:");
                break;
            case ROW2COL6:
                SEND_STRING(":pepeLaugh:");
                break;
            case ROW3COL6:
                SEND_STRING(":clownCake:");
                break;
            case ROW4COL6:
                SEND_STRING(":pepecross~1:");
                break;
            case ROW0COL7:
                SEND_STRING(":umm2~1:");
                break;
            case ROW1COL7:
                SEND_STRING(":jim:");
                break;
            case ROW2COL7:
                SEND_STRING(":smudge:");
                break;
            case ROW3COL7:
                SEND_STRING(":broden~1:");
                break;
            case ROW4COL7:
                SEND_STRING(":SoGood:");
                break;
            case ROW0COL8:
                SEND_STRING(":oncoming_police_car:");
                break;
            case ROW1COL8:
                SEND_STRING(":galaxybrane:");
                break;
            case ROW2COL8:
                SEND_STRING(":stonks:");
                break;
            case ROW3COL8:
                SEND_STRING(":Flip:");
                break;
            case ROW4COL8:
                SEND_STRING(":flag_ph:");
                break;
            case ROW0COL9:
                SEND_STRING(":spamblob~1:");
                break;
            case ROW1COL9:
                SEND_STRING(":tortinanom:");
                break;
            case ROW2COL9:
                SEND_STRING(":taerage:");
                break;
            case ROW3COL9:
                SEND_STRING(":MendezRage:");
                break;
            case ROW4COL9:
                SEND_STRING(":flag_au:");
                break;
            case ROW0COL10:
                SEND_STRING(":pray:");
                break;
            case ROW1COL10:
                SEND_STRING(":eyes:");
                break;
            case ROW2COL10:
                SEND_STRING(":thinkys:");
                break;
            case ROW3COL10:
                SEND_STRING(":thumbsup:");
                break;
            case ROW4COL10:
                SEND_STRING(":thumbsdown:");
                break;
            case ROW0COL11:
                SEND_STRING(":partying_face:");
                break;
            case ROW1COL11:
                SEND_STRING(":careblob:");
                break;
            case ROW2COL11:
                SEND_STRING(":smiling_face_with_3_hearts:");
                break;
            case ROW3COL11:
                SEND_STRING(":heart_eyes:");
                break;
            case ROW4COL11:
                SEND_STRING(":heart:");
                break;
        }
    } else {
        switch (keycode) {
            case ROW0COL0 ... ROW4COL11:
                if (timer_elapsed(key_timer) > 200) {
                    SEND_STRING("\n");
                }
                break;  
        }
    }
    return true;
};
