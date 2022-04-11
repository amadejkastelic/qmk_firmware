/* Copyright 2020 Harrison Chan (Xelus)
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

// Nothing to see here, move along... ;-)

#include "jmun_bear65.h"

#ifdef RGB_MATRIX_ENABLE

// ["~\n`",{x:0.25},"~\n`","!\n1","@\n2","#\n3","$\n4","%\n5","^\n6","&\n7","*\n8","(\n9",")\n0","_\n-","+\n=",{w:2},"Backspace",{x:0.25},"Alt"],
// ["!\n1",{x:0.25,w:1.5},"Tab","Q","W","E","R","T","Y","U","I","O","P","{\n[","}\n]",{w:1.5},"|\n\\"],
// ["@\n2",{x:0.25,w:1.75},"Caps Lock","A","S","D","F","G","H","J","K","L",":\n;","\"\n'",{w:2.25},"Enter"],
// [{x:1.25,w:2.25},"Shift","Z","X","C","V","B","N","M","<\n,",">\n.","?\n/",{w:1.75},"Shift","?\n/"],
// [{x:1.25,w:1.25},"Ctrl",{x:1.25,w:1.25},"Alt",{a:7,w:2.25},"",{a:4},"B",{x:1.25,a:7,w:2.75},"",{a:4},"B",{x:1},"Win","Menu","Ctrl"]
#define XXX NO_LED
led_config_t g_led_config = { {
  // Key Matrix to LED Index
    {   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14, XXX }, 
    {  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  16 }, 
    {  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43, XXX,  44,  31 }, 
    {  45,   0,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58 }, 
    {  59, XXX, XXX,  60, XXX,  61,  62, XXX,  63, XXX,  64,  65,  66,  67,  15 },
}, {
  // LED Index to Physical Position
    {  0,0  }, { 16,0  }, { 29,0  }, { 42,0  }, { 54,0  }, { 67,0  }, { 80,0  }, { 93,0  }, {118,0  }, {131,0  }, 
    {144,0  }, {157,0  }, {170,0  }, {182,0  }, {202,0  }, {224,0  }, {  0,16 }, { 19,16 }, { 35,16 }, { 48,16 }, 
    { 61,16 }, { 74,16 }, { 86,16 }, { 99,16 }, {125,16 }, {138,16 }, {150,16 }, {163,16 }, {176,16 }, {189,16 }, 
    {205,16 }, {  0,32 }, { 21,32 }, { 38,32 }, { 51,32 }, { 64,32 }, { 77,32 }, { 90,32 }, {102,32 }, {128,32 }, 
    {141,32 }, {154,32 }, {166,32 }, {179,32 }, {200,32 }, { 24,48 }, { 45,48 }, { 58,48 }, { 70,48 }, { 83,48 }, 
    { 96,48 }, {109,48 }, {122,48 }, {134,48 }, {147,48 }, {160,48 }, {173,48 }, {190,48 }, {208,48 }, { 18,64 }, 
    { 56,64 }, { 78,64 }, { 99,64 }, {136,64 }, {160,64 }, {195,64 }, {208,64 }, {221,64 }, 
}, {
  // LED Index to Flag
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
#endif
