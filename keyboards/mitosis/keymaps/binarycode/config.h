/*
Copyright 2019 Igor Sidorov <igor.sidorov@binarycode.ru> @binarycode

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

#pragma once

// TODO: TEST is this needed?
#include "../../config.h"

#define MK_3_SPEED
#define MK_C_OFFSET_SLOW   2
#define MK_C_INTERVAL_SLOW 12
#define MK_C_OFFSET_MED    8
#define MK_C_INTERVAL_MED  16
#define MK_C_OFFSET_FAST   12
#define MK_C_INTERVAL_FAST 16

#define LAYOUT_kc( \
  k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09, \
  k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19, \
  k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29, \
       k31, k32, k33, k34,      k35, k36, k37, k38,      \
       k41, k42, k43, k44,      k45, k46, k47, k48       \
) \
{ \
  { KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09 }, \
  { KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19 }, \
  { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29 }, \
  { KC_NO,    KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, KC_##k37, KC_##k38, KC_NO    }, \
  { KC_NO,    KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45, KC_##k46, KC_##k47, KC_##k48, KC_NO    }  \
}

#define TAPPING_TERM 200
