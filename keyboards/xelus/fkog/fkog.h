/*
Copyright 2018 Jumail Mundekkat / MxBlue

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

  /*K11,      K31, K41, K51, K61,      K81, K91, KA1, KB1,      KC1, K01, KD1, K21,      K20, K30, K00, \
                                                                                                      \
  K12, K22, K32, K42, K52, K62,  K72,  K82,  K92,  KA2,  KB2, KC2, K02,   KD2   ,      K70, K60, K50, \
   K13  , K23, K33, K43, K53, K63,  K73,  K83,  K93,  KA3,  KB3, KC3, K03,  KD3 ,      KD0, K90, K80, \
     K15  , K25, K35, K45, K55, K65,  K75,  K85,  K95,  KA5,  KB5, KC5,   K05   ,                     \
      K16  , K26, K36, K46, K56, K66,  K76,  K86,  K96,  KA6,  KB6,   KC6  , K06,           KD6,      \
  K17 , K27 , K37 ,                K57                  , K97 , KA7 , KB7 , KC7 ,      K07, KD7, K87  \
  */
#pragma once

#include "quantum.h"

#define ____ KC_NO

#define LAYOUT_all( \
    K000,       K002, K003, K004, K005,   K600, K606, K706, K700,   K007, K008, K009, K010,    K409, K410, K310, \
                                                                                                                 \
    K100, K101, K102, K103, K104, K105, K601, K607, K707, K701, K106, K107, K108, K109, K110,  K509, K510, K713, \
    K200, K201, K202, K203, K204, K205, K602, K608, K708, K702, K206, K207, K208, K209,        K711, K712, K714, \
    K300, K301, K302, K303, K304, K305, K603, K609, K709, K703, K306, K307, K309,                                \
    K400, K401, K402, K403, K404, K405, K604, K610, K710, K704, K406, K407, K408,                    K614,       \
    K500, K501, K502,                   K605,             K705, K506, K507, K508,              K611, K612, K613  \
){ \
  { K000, ____, K002, K003, K004, K005, ____, K007, K008, K009, K010, ____, ____, ____, ____ }, \
  { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, ____, ____, ____, ____ }, \
  { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, ____, ____, ____, ____, ____ }, \
  { K300, K301, K302, K303, K304, K305, K306, K307, ____, K309, K310, ____, ____, ____, ____ }, \
  { K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, ____, ____, ____, ____ }, \
  { K500, K501, K502, ____, ____, ____, K506, K507, K508, K509, K510, ____, ____, ____, ____ }, \
  { K600, K601, K602, K603, K604, K605, K606, K607, K608, K609, K610, K611, K612, K613, K614 }, \
  { K700, K701, K702, K703, K704, K705, K706, K707, K708, K709, K710, K711, K712, K713, K714 } \
}
