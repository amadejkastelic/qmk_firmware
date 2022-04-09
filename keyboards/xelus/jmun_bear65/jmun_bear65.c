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
    {  59, XXX, XXX,  60, XXX,  61,  62, XXX,  63, XXX,  64,  65,  66, XXX,  15 }, 
}, {
  // LED Index to Physical Position
    {  0,0  }, { 17,0  }, { 31,0  }, { 44,0  }, { 58,0  }, { 71,0  }, { 85,0  }, { 98,0  }, {112,0  }, {126,0  }, 
    {139,0  }, {153,0  }, {166,0  }, {180,0  }, {200,0  }, {224,0  }, {  0,16 }, { 20,16 }, { 37,16 }, { 51,16 }, 
    { 64,16 }, { 78,16 }, { 92,16 }, {105,16 }, {119,16 }, {132,16 }, {146,16 }, {160,16 }, {173,16 }, {187,16 }, 
    {204,16 }, {  0,32 }, { 22,32 }, { 41,32 }, { 54,32 }, { 68,32 }, { 81,32 }, { 95,32 }, {109,32 }, {122,32 }, 
    {136,32 }, {149,32 }, {163,32 }, {176,32 }, {199,32 }, { 25,48 }, { 48,48 }, { 61,48 }, { 75,48 }, { 88,48 }, 
    {102,48 }, {115,48 }, {129,48 }, {143,48 }, {156,48 }, {170,48 }, {188,48 }, {207,48 }, { 19,64 }, { 53,64 }, 
    { 76,64 }, { 98,64 }, {141,64 }, {166,64 }, {193,64 }, {207,64 }, {221,64 }, 
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
