/* Copyright 2021 geek-rabb1t
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

#include "timothy.h"



#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  //left
  {      26, 27, 28, 29, 30, 31, 32 },
  {      25, 24, 23, 22, 21, 20, 19 },
  {      12, 13, 14, 15, 16, 17, 18 },
  {      11, 10,  9,  8,  7,  6,  5 },
  {  NO_LED,  3,  4,  0,  1,  2, NO_LED },
  //right
  {      39, 38, 37, 36, 35, 34, 33 },
  {      40, 41, 42, 43, 44, 45, 46 },
  {      53, 52, 51, 50, 49, 48, 47 },
  {      54, 55, 56, 57, 58, 59, 60 },
  {  NO_LED, 62, 61, 63, 64, 65, NO_LED },
}, {
  // LED Index to Physical Position
  //left
  {   0,   0 }, {  17,   0 }, {  34,   0 }, {  52,   0 }, {   69,   0 }, {   86,   0 }, {  103,   0 },
  {   0,  16 }, {  17,  16 }, {  34,  16 }, {  52,  16 }, {   69,  16 }, {   86,  16 }, {  103,  16 },
  {   0,  32 }, {  17,  32 }, {  34,  32 }, {  52,  32 }, {   69,  32 }, {   86,  32 }, {  103,  32 },
  {   0,  48 }, {  17,  48 }, {  34,  48 }, {  52,  48 }, {   69,  48 }, {   86,  48 }, {  103,  48 },
                {  17,  64 }, {  34,  64 }, {  52,  64 }, {   69,  64 }, {   86,  64 },
  //right
  { 224,   0 }, { 207,   0 }, { 190,   0 }, { 172,   0 }, {  155,   0 }, {  138,   0 }, {  121,   0 },
  { 224,  16 }, { 207,  16 }, { 190,  16 }, { 172,  16 }, {  155,  16 }, {  138,  16 }, {  121,  16 },
  { 224,  32 }, { 207,  32 }, { 190,  32 }, { 172,  32 }, {  155,  32 }, {  138,  32 }, {  121,  32 },
  { 224,  48 }, { 207,  48 }, { 190,  48 }, { 172,  48 }, {  155,  48 }, {  138,  48 }, {  121,  48 },
                { 207,  64 }, { 190,  64 }, { 172,  64 }, {  155,  64 }, {  138,  64 },
}, {
  // LED Index to Flag
  // left
  4, 4, 4, 4, 4, 4, 0xFF,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4,
  // right
  4, 4, 4, 4, 4, 4, 0xFF,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4,
} };

#endif
