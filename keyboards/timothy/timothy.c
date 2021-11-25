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
  {       0,  1,  2,  3,  4,  5,  6 },
  {       7,  8,  9, 10, 11, 12, 13 },
  {      14, 15, 16, 17, 18, 19, 20 },
  {      21, 22, 23, 24, 25, 26, 27 },
  {  NO_LED, 28, 29, 30, 31, 32, 33 },
 // {      34, 35, 36, 37, 38, 39, 40 },
  //right
  {      47, 46, 45, 44, 43, 42, 41 },
  {      54, 53, 52, 51, 50, 49, 48 },
  {      61, 60, 59, 58, 57, 56, 55 },
  {      68, 67, 66, 65, 64, 63, 62 },
  {  NO_LED, 74, 73, 72, 71, 70, 69 },
 // {      81, 80, 79, 78, 77, 76, 75 },
}, {
  // LED Index to Physical Position
  //left
  {   0,   0 }, {  17,   0 }, {  34,   0 }, {  52,   0 }, {   69,   0 }, {   86,   0 }, {  103,   0 },
  {   0,  16 }, {  17,  16 }, {  34,  16 }, {  52,  16 }, {   69,  16 }, {   86,  16 }, {  103,  16 },
  {   0,  32 }, {  17,  32 }, {  34,  32 }, {  52,  32 }, {   69,  32 }, {   86,  32 }, {  103,  32 },
  {   0,  48 }, {  17,  48 }, {  34,  48 }, {  52,  48 }, {   69,  48 }, {   86,  48 }, {  103,  48 },
                {  17,  64 }, {  34,  64 }, {  52,  64 }, {   69,  64 }, {   86,  64 }, {  103,  64 },
//  {   0,  64 }, {  17,  64 }, {  34,  64 }, {  52,  64 }, {   69,  64 }, {   86,  64 }, {  103,  64 },
  //right
  { 224,   0 }, { 207,   0 }, { 190,   0 }, { 172,   0 }, {  155,   0 }, {  138,   0 }, {  121,   0 },
  { 224,  16 }, { 207,  16 }, { 190,  16 }, { 172,  16 }, {  155,  16 }, {  138,  16 }, {  121,  16 },
  { 224,  32 }, { 207,  32 }, { 190,  32 }, { 172,  32 }, {  155,  32 }, {  138,  32 }, {  121,  32 },
  { 224,  48 }, { 207,  48 }, { 190,  48 }, { 172,  48 }, {  155,  48 }, {  138,  48 }, {  121,  48 },
                { 207,  64 }, { 190,  64 }, { 172,  64 }, {  155,  64 }, {  138,  64 }, {  121,  64 },
//  { 224,  64 }, { 207,  64 }, { 190,  64 }, { 172,  64 }, {  155,  64 }, {  138,  64 }, {  121,  64 }
}, {
  // LED Index to Flag
  // left
  4, 4, 4, 4, 4, 4, 0xFF,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4,
//  2, 2, 2, 2, 2, 2, 2,
  // right
  4, 4, 4, 4, 4, 4, 0xFF,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
     4, 4, 4, 4, 4, 4,
//  2, 2, 2, 2, 2, 2, 2
} };

#endif
