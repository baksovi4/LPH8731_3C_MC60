/*
 LPH8731_3C_MC60.cpp

 Created by BAKS
 Date: November 2019.

 PERMISSION TO DISTRIBUTE

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.


 LIMITATION OF LIABILITY

 The software is provided "as is", without warranty of any kind, express or implied,
 including but not limited to the warranties of merchantability, fitness for a particular
 purpose and noninfringement. In no event shall the authors or copyright holders be liable
 for any claim, damages or other liability, whether in an action of contract,
 tort or otherwise, arising from, out of or in connection with the software
 or the use or other dealings in the software.

 */

#include "Arduino.h"
#include "LPH8731_3C_MC60.h"

/********************************************************************************************
* 	
*  	   	   ____
* 		 _|__1_|_
* 		|6|    |2|
* 		|_|____|_|
* 		 _|__7_|_
* 		|5|    |3|
* 		|_|____|_|
* 		  |__4_|
*
********************************************************************************************//*
const char clock [10] [7] PROGMEM = {
		{1,1,1,1,1,1,0}, // 0
		{0,1,1,0,0,0,0}, // 1
		{1,1,0,1,1,0,1}, // 2
		{1,1,1,1,0,0,1}, // 3
		{0,1,1,0,0,1,1}, // 4
		{1,0,1,1,0,1,1}, // 5
		{1,0,1,1,1,1,1}, // 6
		{1,1,1,0,0,0,0}, // 7
		{1,1,1,1,1,1,1}, // 8
		{1,1,1,1,0,1,1}  // 9
};*/

// font data - each character is 8 pixels deep and 5 pixels wide with RUS

const char font [256] [5] PROGMEM = {
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  0
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  1
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  2
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  3
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  4
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  5
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  6
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  7
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  8
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  9
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  10
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  11
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  12
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  13
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  14
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  15
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  16
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  17
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  18
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  19
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  20
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  21
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  22
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  23
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  24
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  25
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  26
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  27
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  28
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  29
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  30
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  31
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  32
  {0x00, 0x00, 0x5F, 0x00, 0x00}, // !        33
  {0x00, 0x07, 0x00, 0x07, 0x00}, // "        34
  {0x14, 0x7F, 0x14, 0x7F, 0x14}, // #        35
  {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $        36
  {0x23, 0x13, 0x08, 0x64, 0x62}, // %        37
  {0x36, 0x49, 0x55, 0x22, 0x50}, // &        38
  {0x00, 0x05, 0x03, 0x00, 0x00}, // '        39
  {0x00, 0x1C, 0x22, 0x41, 0x00}, // (        40
  {0x00, 0x41, 0x22, 0x1C, 0x00}, // )        41
  {0x08, 0x2A, 0x1C, 0x2A, 0x08}, // *        42
  {0x08, 0x08, 0x3E, 0x08, 0x08}, // +        43
  {0x00, 0x50, 0x30, 0x00, 0x00}, //          44
  {0x08, 0x08, 0x08, 0x08, 0x08}, // -        45
  {0x00, 0x30, 0x30, 0x00, 0x00}, // .        46
  {0x20, 0x10, 0x08, 0x04, 0x02}, // /        47
  {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0        48
  {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1        49
  {0x42, 0x61, 0x51, 0x49, 0x46}, // 2        50
  {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3        51
  {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4        52
  {0x27, 0x45, 0x45, 0x45, 0x39}, // 5        53
  {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6        54
  {0x01, 0x71, 0x09, 0x05, 0x03}, // 7        55
  {0x36, 0x49, 0x49, 0x49, 0x36}, // 8        56
  {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9        57
  {0x00, 0x36, 0x36, 0x00, 0x00}, // :        58
  {0x00, 0x56, 0x36, 0x00, 0x00}, // ;        59
  {0x00, 0x08, 0x14, 0x22, 0x41}, // <        60
  {0x14, 0x14, 0x14, 0x14, 0x14}, // =        61
  {0x41, 0x22, 0x14, 0x08, 0x00}, // >        62
  {0x02, 0x01, 0x51, 0x09, 0x06}, // ?        63
  {0x32, 0x49, 0x79, 0x41, 0x3E}, // @        64
  {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A        65
  {0x7F, 0x49, 0x49, 0x49, 0x36}, // B        66
  {0x3E, 0x41, 0x41, 0x41, 0x22}, // C        67
  {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D        68
  {0x7F, 0x49, 0x49, 0x49, 0x41}, // E        69
  {0x7F, 0x09, 0x09, 0x01, 0x01}, // F        70
  {0x3E, 0x41, 0x41, 0x51, 0x32}, // G        71
  {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H        72
  {0x00, 0x41, 0x7F, 0x41, 0x00}, // I        73
  {0x20, 0x40, 0x41, 0x3F, 0x01}, // J        74
  {0x7F, 0x08, 0x14, 0x22, 0x41}, // K        75
  {0x7F, 0x40, 0x40, 0x40, 0x40}, // L        76
  {0x7F, 0x02, 0x04, 0x02, 0x7F}, // M        77
  {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N        78
  {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O        79
  {0x7F, 0x09, 0x09, 0x09, 0x06}, // P        80
  {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q        81
  {0x7F, 0x09, 0x19, 0x29, 0x46}, // R        82
  {0x46, 0x49, 0x49, 0x49, 0x31}, // S        83
  {0x01, 0x01, 0x7F, 0x01, 0x01}, // T        84
  {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U        85
  {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V        86
  {0x7F, 0x20, 0x18, 0x20, 0x7F}, // W        87
  {0x63, 0x14, 0x08, 0x14, 0x63}, // X        88
  {0x03, 0x04, 0x78, 0x04, 0x03}, // Y        89
  {0x61, 0x51, 0x49, 0x45, 0x43}, // Z        90
  {0x00, 0x00, 0x7F, 0x41, 0x41}, // [        91
  {0x02, 0x04, 0x08, 0x10, 0x20}, // "\"      92
  {0x41, 0x41, 0x7F, 0x00, 0x00}, // ]        93
  {0x04, 0x02, 0x01, 0x02, 0x04}, // ^        94
  {0x40, 0x40, 0x40, 0x40, 0x40}, // _        95
  {0x00, 0x01, 0x02, 0x04, 0x00}, // `        96
  {0x20, 0x54, 0x54, 0x54, 0x78}, // a        97
  {0x7F, 0x48, 0x44, 0x44, 0x38}, // b        98
  {0x38, 0x44, 0x44, 0x44, 0x20}, // c        99
  {0x38, 0x44, 0x44, 0x48, 0x7F}, // d        100
  {0x38, 0x54, 0x54, 0x54, 0x18}, // e        101
  {0x08, 0x7E, 0x09, 0x01, 0x02}, // f        102
  {0x08, 0x14, 0x54, 0x54, 0x3C}, // g        103
  {0x7F, 0x08, 0x04, 0x04, 0x78}, // h        104
  {0x00, 0x44, 0x7D, 0x40, 0x00}, // i        105
  {0x20, 0x40, 0x44, 0x3D, 0x00}, // j        106
  {0x00, 0x7F, 0x10, 0x28, 0x44}, // k        107
  {0x00, 0x41, 0x7F, 0x40, 0x00}, // l        108
  {0x7C, 0x04, 0x18, 0x04, 0x78}, // m        109
  {0x7C, 0x08, 0x04, 0x04, 0x78}, // n        110
  {0x38, 0x44, 0x44, 0x44, 0x38}, // o        111
  {0x7C, 0x14, 0x14, 0x14, 0x08}, // p        112
  {0x08, 0x14, 0x14, 0x18, 0x7C}, // q        113
  {0x7C, 0x08, 0x04, 0x04, 0x08}, // r        114
  {0x48, 0x54, 0x54, 0x54, 0x20}, // s        115
  {0x04, 0x3F, 0x44, 0x40, 0x20}, // t        116
  {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u        117
  {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v        118
  {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w        119
  {0x44, 0x28, 0x10, 0x28, 0x44}, // x        120
  {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y        121
  {0x44, 0x64, 0x54, 0x4C, 0x44}, // z        122
  {0x00, 0x08, 0x36, 0x41, 0x00}, // {        123
  {0x00, 0x00, 0x7F, 0x00, 0x00}, // |        124
  {0x00, 0x41, 0x36, 0x08, 0x00}, // }        125
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  126
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  127
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  128
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  129
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  130
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  131
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  132
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  133
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  134
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  135
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  136
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  137
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  138
  {0x08, 0x1C, 0x2A, 0x08, 0x08}, // <-       139
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  140
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  141
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  142
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  143
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  144
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  145
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  146
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  147
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  148
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  149
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  150
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  151
  {127, 65, 65, 65, 127},         //  Пустой квадрат  152
  {127, 127, 127, 127, 127},      //  Заполн квадрат  153
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  154
  {28, 127, 62, 28, 8},           // ->       155
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  156
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  157
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  158
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  159
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  160
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  161
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  162
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  163
  {184, 69, 95, 85, 184},         // Значек будильника  164,
  {16, 30, 31, 62, 16},           // Колокольчик        165,
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  166
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  167
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  168
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  169
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  170
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  171
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  172
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  173
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  174
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  175
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  176
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  177
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  178
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  179
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  180
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  181
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  182
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  183
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  184
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  185
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  186
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  187
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  188
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  189
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  190
  {0x00, 0x00, 0x00, 0x00, 0x00}, // (space)  191
  {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A        192
  {0x7F, 0x45, 0x45, 0x45, 0x39}, // Б        193
  {0x7F, 0x49, 0x49, 0x49, 0x36}, // B        194
  {0x7F, 0x01, 0x01, 0x01, 0x03}, // Г        195
  {0xC0, 0x7E, 0x41, 0x7F, 0xC0}, // Д        196
  {0x7F, 0x49, 0x49, 0x49, 0x41}, // E        197
  {119, 8, 127, 8, 119},          // Ж        198
  {34, 73, 73, 73, 54},           // З        199
  {127, 32, 16, 8, 127},          // И        200
  {127, 32, 19, 8, 127},          // Й        201
  {0x7F, 0x08, 0x14, 0x22, 0x41}, // K        202
  {64, 62, 1, 1, 127},            // Л        203
  {0x7F, 0x02, 0x04, 0x02, 0x7F}, // M        204
  {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H        205
  {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O        206
  {127, 1, 1, 1, 127},            // П        207
  {0x7F, 0x09, 0x09, 0x09, 0x06}, // P        208
  {0x3E, 0x41, 0x41, 0x41, 0x22}, // C        209
  {0x01, 0x01, 0x7F, 0x01, 0x01}, // T        210
  {39, 72, 72, 72, 63},           // У        211
  {30, 33, 127, 33, 30},          // Ф        212
  {0x63, 0x14, 0x08, 0x14, 0x63}, // X        213
  {127, 64, 64, 127, 192},        // Ц        214
  {15, 16, 16, 16, 127},          // Ч        215
  {127, 64, 124, 64, 127},        // Ш        216
  {127, 64, 124, 64, 255},        // Щ        217
  {1, 127, 72, 72, 48},           // Ъ        218
  {127, 72, 48, 0, 127},          // Ы        219
  {127, 72, 72, 72, 48},          // Ь        220
  {34, 73, 73, 73, 62},           // Э        221
  {127, 8, 62, 65, 62},           // Ю        222
  {118, 9, 9, 9, 127},            // Я        223
  {0x20, 0x54, 0x54, 0x54, 0x78}, // a        224
  {124, 84, 84, 84, 36},          // б        225
  {124, 84, 84, 84, 40},          // в        226
  {124, 4, 4, 4, 12},             // г        227
  {192, 120, 68, 124, 192},       // д        228
  {0x38, 0x54, 0x54, 0x54, 0x18}, // e        229
  {108, 16, 124, 16, 108},        // ж        230
  {40, 68, 84, 84, 40},           // з        231
  {124, 32, 16, 8, 124},          // и        232
  {124, 33, 18, 8, 124},          // й        233
  {124, 16, 16, 40, 68},          // к        234
  {64, 56, 4, 4, 124},            // л        235
  {124, 8, 16, 8, 124},           // м        236
  {124, 16, 16, 16, 124},         // н        237
  {0x38, 0x44, 0x44, 0x44, 0x38}, // o        238
  {124, 4, 4, 4, 124},            // п        239
  {0x7C, 0x14, 0x14, 0x14, 0x08}, // p        240
  {0x38, 0x44, 0x44, 0x44, 0x20}, // c        241
  {4, 4, 124, 4, 4},              // т        242
  {0x0C, 0x50, 0x50, 0x50, 0x3C}, // y        243
  {24, 36, 124, 36, 24},          // ф        244
  {0x44, 0x28, 0x10, 0x28, 0x44}, // x        245
  {124, 64, 64, 124, 192},        // ц        246
  {12, 16, 16, 16, 124},          // ч        247
  {124, 64, 120, 64, 124},        // ш        248
  {124, 64, 120, 64, 252},        // щ        249
  {124, 84, 80, 80, 32},          // ъ        250
  {124, 80, 32, 0, 124},          // ы        251
  {124, 80, 80, 80, 32},          // ь        252
  {40, 68, 84, 84, 56},           // э        253
  {124, 16, 56, 68, 56},          // ю        254
  {72, 52, 20, 20, 124}           // я        255
};

//*************************************************************
//COMMAND/DATA
#define CMD   0
#define DAT   1

char RS_old;


void work_cs (boolean a)
{
  digitalWrite(LCD_CS, a);
}

void work_clk (boolean a)
{
  digitalWrite(LCD_CLK, a);
}

void work_res (boolean a)
{
  digitalWrite(LCD_RESET, a);
}

void work_rs (boolean a)
{
  digitalWrite(LCD_RS, a);
}

void work_data (boolean a)
{
  digitalWrite(LCD_DATA, a);
}


//===============================================================
//                           RESET LCD
//===============================================================
void LPH8731_3C_MC60::reset (void)
{
  work_cs(0);
  work_data(0);
  work_res(0);
  //delay(100);
  work_res(1);;
  //delay(500);
  work_cs(1);
  //delay(5);
  work_cs(0);
} // END LPH8731_3C_MC60::reset


//===============================================================
//                   LCD INICIALIZATION
//===============================================================
void LPH8731_3C_MC60::begin (void)
{
  // Set pins to output direction
  pinMode (LCD_CS, 	OUTPUT);
  pinMode (LCD_RESET, 	OUTPUT);
  pinMode (LCD_RS, 	OUTPUT);
  pinMode (LCD_CLK, 	OUTPUT);
  pinMode (LCD_DATA, 	OUTPUT);

  reset();
  lcdSend(CMD, 0x01); // reset sw
  //delay(50);
  lcdSend(CMD, 0xc6); // initial escape
  //delay(40);
  lcdSend(CMD, 0xb9); // Refresh set
  lcdSend(DAT, 0x00);
  lcdSend(CMD, 0xb6); // Display control
  lcdSend(DAT, 0x80); //
  lcdSend(DAT, 0x04); //
  lcdSend(DAT, 0x8a); //
  lcdSend(DAT, 0x54); //
  lcdSend(DAT, 0x45); //
  lcdSend(DAT, 0x52); //
  lcdSend(DAT, 0x43); //
  lcdSend(CMD, 0xb3); // Gray scale position set 0
  lcdSend(DAT, 0x02); //
  lcdSend(DAT, 0x0a); //
  lcdSend(DAT, 0x15); //
  lcdSend(DAT, 0x1f); //
  lcdSend(DAT, 0x28); //
  lcdSend(DAT, 0x30); //
  lcdSend(DAT, 0x37); //
  lcdSend(DAT, 0x3f); //
  lcdSend(DAT, 0x47); //
  lcdSend(DAT, 0x4c); //
  lcdSend(DAT, 0x54); //
  lcdSend(DAT, 0x65); //
  lcdSend(DAT, 0x75); //
  lcdSend(DAT, 0x80); //
  lcdSend(DAT, 0x85); //
  lcdSend(CMD, 0xb5); // Gamma curve
  lcdSend(DAT, 0x01); //
  lcdSend(CMD, 0xb7); // Temperature gradient
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x00); //
  lcdSend(CMD, 0xbd); // Common driver output select
  lcdSend(DAT, 0x00); //
  /*
	    lcdSend(CMD,0x33); // Vertical scrolling definition
	    lcdSend(DAT,0x00); // max - 0x53
	    lcdSend(DAT,0x53); //
	    lcdSend(DAT,0x00); //
	    lcdSend(CMD,0x37); //Vertical scrolling start adress
	    lcdSend(DAT,0x00);
  */
  lcdSend(CMD, 0x36); // Memory access control
  lcdSend(DAT, 0x48); //
  lcdSend(CMD, 0x2d); // Colour set
  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x03); //
  lcdSend(DAT, 0x05); //
  lcdSend(DAT, 0x07); //
  lcdSend(DAT, 0x09); //
  lcdSend(DAT, 0x0b); //
  lcdSend(DAT, 0x0d); //
  lcdSend(DAT, 0x0f); //

  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x03); //
  lcdSend(DAT, 0x05); //
  lcdSend(DAT, 0x07); //
  lcdSend(DAT, 0x09); //
  lcdSend(DAT, 0x0b); //
  lcdSend(DAT, 0x0d); //
  lcdSend(DAT, 0x0f); //

  lcdSend(DAT, 0x00); //
  lcdSend(DAT, 0x05); //
  lcdSend(DAT, 0x0b); //
  lcdSend(DAT, 0x0f); //
  lcdSend(CMD, 0xba); // Voltage control
  lcdSend(DAT, 0x2f); //
  lcdSend(DAT, 0x03); //
  lcdSend(CMD, 0x25); // Write contrast
  lcdSend(DAT, 0x61); //
  lcdSend(CMD, 0xbe); // Power control
  lcdSend(DAT, 0x58); // 0x58 before

  lcdSend(CMD, 0x3a); // interface pixel format

#ifdef _8_BIT_COLOR
  lcdSend(DAT, 0x02); // 0x02 for 8-bit
#else
  lcdSend(DAT, 0x03); // 0x03 for 12bit
#endif

  lcdSend(CMD, 0x03); // Booster voltage ON
  //delay(40);
  lcdSend(CMD, 0x11); // sleep out

  //delay(20);        // 20
  lcdSend(CMD, 0x29); // Display ON
} // END LPH8731_3C_MC60::begin


//*******************************************************************
//
//*******************************************************************
void LPH8731_3C_MC60::lcdSend (unsigned char RS, unsigned char data)
{
  work_clk(0);
  work_data(0);
  if ((RS_old != RS) || (!RS_old && !RS))
  {
    work_cs(1);
    digitalWrite(LCD_RS, RS); // = RS;
    work_cs(0);
  }

  work_data(0);
  if ((data & 128) == 128) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 64) == 64) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 32) == 32) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 16) == 16) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 8) == 8) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 4) == 4) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 2) == 2) work_data(1);
  work_clk(1);
  work_clk(0);
  work_data(0);
  if ((data & 1) == 1) work_data(1);
  work_clk(1);
  work_clk(0);

  RS_old = RS; //  RS
  work_data(0);
} // END LPH8731_3C_MC60::Send_to_lcd


//*******************************************************************
//  установка площади
//*******************************************************************
void LPH8731_3C_MC60::setArea (char x1, char x2, char y1, char y2)
{
  lcdSend( CMD, 0x2A );  // задаем область по X (x0 - начальный, x1 - конечный)
  lcdSend( DAT, x1 );    //
  lcdSend( DAT, x2 );    //

  lcdSend( CMD, 0x2B );   // задаем область по Y (y0 - начальный, y1 - конечный)
  lcdSend( DAT, y1 + 1 ); // у этого контроллера Y отсчитывается от 1, а не 0
  lcdSend( DAT, y2 + 1 ); //

  lcdSend( CMD, 0x2C );  // отправляем команду на начало записи в память и начинаем посылать данные
} // END LPH8731_3C_MC60::setArea


//*******************************************************************
//   Функция заливки экрана белым цветом 
//*******************************************************************
void LPH8731_3C_MC60::white (void)
{
	fillScreen (255);
}


//*******************************************************************
//   Функция заливки экрана черным цветом 
//*******************************************************************
void LPH8731_3C_MC60::black (void)
{
	fillScreen (0); 
}

//*******************************************************************
//   Функция заливки экрана цветом color
//*******************************************************************
void LPH8731_3C_MC60::fillScreen (unsigned int color)
{
  unsigned int x;
  signed char i;
  setArea( 0, 100, 0, 80 );   //
  for (x = 0; x < 8080; x++)
  {
#ifdef _8_BIT_COLOR        //(8-BIT (256 COLOR))
    lcdSend( DAT, color ); //
#else                     //(12-BIT (4096 COLOR))
    lcdSend( DAT, color >> 4 );
    lcdSend( DAT, (color << 4) | (color >> 8) );
    lcdSend( DAT, color ); x++; //
#endif
  }
} // END LPH8731_3C_MC60:fillScreen


//*******************************************************************
//  Функция вывода точки (пикселя). x и y – координаты экрана, где будет отображён пиксель цветом color.
//*******************************************************************
void LPH8731_3C_MC60::setPixColor (char x, char y, unsigned int color)
{
  signed char i;
  setArea( x, x, y, y );
#ifdef _8_BIT_COLOR
  lcdSend( DAT, color );
#else
  lcdSend( DAT, color >> 4 );
  lcdSend( DAT, color << 4 );
#endif
}	// LPH8731_3C_MC60


//*******************************************************************
//  Функция вывода одного символа из массива font[]
//  - symbol – выводимый на экран символ
//  - x и y – начальная координата вывода символа
//  - t_color – цвет пикселя; b_color – цвет фона
//  - zoom_width и zoom_height увеличивают символ на экране в указанное число раз
//   ** - плохо работает поворот
//*******************************************************************
void LPH8731_3C_MC60::setSymbol (unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height, int rotation)
{
  unsigned char temp_symbol, a, b, zw, zh, mask;
  char m, n;
  m = x;
  n = y;
  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;

  for ( a = 0; a < 5; a++)
  {

    temp_symbol = font[symbol][a];
    zw = 0;
    while (zw != zoom_width)
    {
      switch (rotation)
      {
        case 0: case 180: n = y; break;
        case 90: case 270: m = x; break;
      }
      mask = 0x01;
      for ( b = 0; b < 8; b++ )
      {
        zh = 0;
        while (zh != zoom_height)
        {
          switch (rotation)
          {
            case 0: case 180:
              if (temp_symbol & mask)
              {
                setPixColor (m + zw, n + zh, t_color);
              }
              else
              {
                setPixColor (m + zw, n + zh, b_color);
              }
              break;
            case 90: case 270:
              if (temp_symbol & mask)
              {
                setPixColor (m + zh, n + zw, t_color);
              }
              else
              {
                setPixColor (m + zh, n + zw, b_color);
              }
              break;
          }
          zh++;
        }
        mask <<= 1;
        switch (rotation)
        {
          case 0: case 180: n = n + zoom_height; break;
          case 90: case 270: m = m + zoom_height; break;
        }
      }
      zw++;
    }
    switch (rotation)
    {
      case 0: case 180: m = m + zoom_width; break;
      case 90: case 270: n = n + zoom_width; break;
    }
  }
} // LPH8731_3C_MC60


//*******************************************************************
//   вывод символа без фонового цвета
//  ** - плохо работает поворот
//*******************************************************************
void LPH8731_3C_MC60::setSymbolShadow (unsigned char symbol, char x, char y, int t_color, char zoom_width, char zoom_height, int rotation)
{
  unsigned char temp_symbol, a, b, zw, zh, mask;
  char m, n;
  m = x;
  n = y;
  for ( a = 0; a < 5; a++)
  {
    temp_symbol = font[symbol][a];
    zw = 0;
    while (zw != zoom_width)
    {
      switch (rotation)
      {
        case 0: case 180: n = y; break;
        case 90: case 270: m = x; break;
      }
      mask = 0x01;
      for ( b = 0; b < 8; b++ )
      {
        zh = 0;
        while (zh != zoom_height)
        {
          switch (rotation)
          {
            case 0: case 180:
              if (temp_symbol & mask)
              {
                setPixColor (m + zw, n + zh, t_color);
              }
              break;
            case 90: case 270:
              if (temp_symbol & mask)
              {
                setPixColor (m + zh, n + zw, t_color);
              }
              break;
          }
          zh++;
        }
        mask <<= 1;
        switch (rotation)
        {
          case 0: case 180: n = n + zoom_height; break;
          case 90: case 270: m = m + zoom_height; break;
        }
      }
      zw++;
    }
    switch (rotation)
    {
      case 0: case 180: m = m + zoom_width; break;
      case 90: case 270: n = n + zoom_width; break;
    }
  }
} // LPH8731_3C_MC60


//*******************************************************************
//  Функция вывода одного символа из массива font[]
//  - symbol – выводимый на экран символ
//  - x и y – начальная координата вывода символа
//  - t_color – цвет пикселя; b_color – цвет фона
//  - zoom_width и zoom_height увеличивают символ на экране в указанное число раз
//  - rotation – угол поворота текста (0º , 90º, 180º, 270º)
//===============================================================
void LPH8731_3C_MC60::setChar (unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height, int rotation)
{
  unsigned char m;
  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;
  switch (rotation)
  {
    case 0:
      setSymbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rotation);
      break;
    //================================
    case 90:
      m = y + 3; y = x; x = m;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x08);
      setSymbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    case 180:
      x += 3; y += 2;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x88);
      setSymbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    case 270:
      m = y; y = x + 2; x = m;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0xC8);
      setSymbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    default:
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      setSymbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      //=================================
  };
} // LPH8731_3C_MC60


//*******************************************************************
//  Функция вывода одного символа из массива font[] без фонового цвета
//*******************************************************************
void LPH8731_3C_MC60::setCharShadow (unsigned char symbol, char x, char y, int t_color, char zoom_width, char zoom_height, int rotation)
{
  unsigned char m;
  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;
  switch (rotation)
  {
    case 0:
      setSymbolShadow( symbol, x, y, t_color, zoom_width, zoom_height, rotation);
      break;
    //================================
    case 90:
      m = y + 3; y = x; x = m;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x08);
      setSymbolShadow( symbol, x, y, t_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    case 180:
      x += 3; y += 2;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x88);
      setSymbolShadow( symbol, x, y, t_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    case 270:
      m = y; y = x + 2; x = m;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0xC8);
      setSymbolShadow( symbol, x, y, t_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    default:
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      setSymbolShadow( symbol, x, y, t_color, zoom_width, zoom_height, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      //=================================
  };
} // LPH8731_3C_MC60

//*******************************************************************
//   вывод строки с фоновым цветом
//*******************************************************************
void LPH8731_3C_MC60::string  (char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height, int rotation)
{
  unsigned char i = 0;

  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;

  while (str[i])
  {
    setSymbol(str[i], x + (i * 6 * zoom_width), y, t_color, b_color, zoom_width, zoom_height, rotation);
    i++;
  }
} // LPH8731_3C_MC60


//*******************************************************************
//   вывод строки без фонового цвета
//*******************************************************************
void LPH8731_3C_MC60::stringShadow (char *str, int x, int y,  int t_color, char zoom_width, char zoom_height, int rotation)
{
  unsigned char i = 0;

  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;

  while (str[i])
  {
    setCharShadow(str[i], x + (i * 6 * zoom_width), y, t_color, zoom_width, zoom_height, rotation);
    i++;
  }
} //LPH8731_3C_MC60


//*******************************************************************
//			Функция вывода картинки. 
//	x и y начальная позиция выводимого на экран изображения; 
//	width и height – ширина и высота изображения (в пикселях); 
//	*img – указатель на массив данных, составляющих изображение; 
//	rotation – угол поворота изображения (0º , 90º, 180º, 270º). 
//  Данная функция предполагает, что массив данных изображения расположен во flash-памяти микроконтроллера. 
//  Для преобразования необходимого изображения в массив, содержащий цвет пикселей, 
//  можно воспользоваться программами Image2Lcd или Nokia Image Creator. 
//  Единственное требование – направление вывода массива изображения должно выполняться слева-направо, сверху-вниз! 
//  При использовании 12-ти битной палитры, при преобразовании изображения в массив типа char, 
//  обязательно старший байт должен идти первым!
//*******************************************************************

void LPH8731_3C_MC60::outputImage (char x, char y, char width, char height, char *img, int rotation)
{
  unsigned char m;
  switch (rotation)
  {
    case 0:
      sendImage (x, y, width, height, img, rotation);
      break;
    //================================
    case 90:
      m = y + 3; y = x; x = m;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x08);
      sendImage (x, y, width, height, img, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      break;
    //================================
    case 180:
      x += 3; y += 2;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x88);
      sendImage (x, y, width, height, img, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x8);
      break;
    //================================
    case 270:
      m = y; y = x + 2; x = m;
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0xC8);
      sendImage (x, y, width, height, img, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x8);
      break;
    //================================
    default:
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      sendImage (x, y, width, height, img, rotation);
      lcdSend(CMD, 0x36);
      lcdSend(DAT, 0x48);
      //=================================
  };
}   // LPH8731_3C_MC60


void LPH8731_3C_MC60::sendImage (char x, char y, char width, char height, char *img, int rotation)
{
  char x1, y1;
  y += 1;
  switch (rotation)
  {
    case 0: case 180:
      for (y1 = y; y1 < (y + height); y1++)
      {
        setArea( x, x + (width - 1), y1, y1 );
        for (x1 = x; x1 < x + width; x1++)
        {
  #ifdef _8_BIT_COLOR
            lcdSend( DAT, *img++ );
  #else
            lcdSend( DAT, (*img << 4) | (*(img + 1) >> 4) ); img++;
            lcdSend( DAT, (*img << 4) | (*(img + 1)) ); img += 2;
            lcdSend( DAT, *img++ ); x1++;
  #endif
        }
      }
      break;

    case 90: case 270:
      for (x1 = x; x1 < x + height; x1++)
      {
        setArea( x1, x1, y, y + (width - 1) );
        for (y1 = y; y1 < y + width; y1++)
        {
  #ifdef _8_BIT_COLOR
            lcdSend( DAT, *img++ );
  #else
            lcdSend( DAT, (*img << 4) | (*(img + 1) >> 4) ); img++;
            lcdSend( DAT, (*img << 4) | (*(img + 1)) ); img += 2;
            lcdSend( DAT, *img++ ); y1++;
  #endif
        }
      }
      break;
  };
} // LPH8731_3C_MC60


//*******************************************************************
//                     GEOMETRIC FIGURES
//*******************************************************************

//*******************************************************************
//	Нарисовать линию. x1 и y1 – начальная позиция линии; x2 и y2 – конечная позиция линии.
//*******************************************************************
void LPH8731_3C_MC60::drawLine (char x1, char y1, char x2, char y2, int color)
{
  short  x, y, d, dx, dy, i, i1, i2, kx, ky;
  signed char flag;

  dx = x2 - x1;
  dy = y2 - y1;
  if (dx == 0 && dy == 0) setPixColor(x1, y1, color);
  else
  {
    kx = 1;
    ky = 1;
    if ( dx < 0 )
    {
      dx = -dx;
      kx = -1;
    }
    else if (dx == 0) kx = 0;
    if (dy < 0)
    {
      dy = -dy;
      ky = -1;
    }
    if (dx < dy)
    {
      flag = 0;
      d = dx;
      dx = dy;
      dy = d;
    }
    else flag = 1;
    i1 = dy + dy;
    d = i1 - dx;
    i2 = d - dx;
    x = x1;
    y = y1;

    for (i = 0; i < dx; i++)
    {
      setPixColor(x, y, color);
      if (flag) x += kx;
      else y += ky;
      if ( d < 0 ) d += i1;
      else
      {
        d += i2;
        if (flag) y += ky;
        else x += kx;
      }
    }
    setPixColor(x, y, color);
  }
} // LPH8731_3C_MC60
 
//*******************************************************************
//		Нарисовать рамку. size - толщина рамки.
//*******************************************************************
void LPH8731_3C_MC60::drawRect (char x1, char y1, char width, char height, char size, int color)
{
  unsigned int i;
  char x2 = x1 + (width - 1), y2 = y1 + (height - 1);
  for ( i = 1; i <= size; i++)
  {
    drawLine(x1, y1, x1, y2, color);
    drawLine(x2, y1, x2, y2, color);
    drawLine(x1, y1, x2, y1, color);
    drawLine(x1, y2, x2, y2, color);
    x1++;
    y1++;
    x2--;
    y2--;
  }
} // LPH8731_3C_MC60


//*******************************************************************
//              Нарисовать прямоугольник.
//*******************************************************************
void LPH8731_3C_MC60::fillRect (char x1, char y1, char width, char height, int color)
{
    unsigned int x, y;
    setArea( x1, x1 + (width - 1), y1, y1 + (height - 1) );
    y = width * height;
    for (x = 0; x < y; x++)
    {
  #ifdef _8_BIT_COLOR
      lcdSend( DAT, color );
      lcdSend( DAT, color );
  #else
      lcdSend( DAT, color >> 4 );
      lcdSend( DAT, (color << 4) | (color >> 8) );
      lcdSend( DAT, color ); x++;
  #endif
    }
} // LPH8731_3C_MC60


//*******************************************************************
//     Нарисовать окружность. rad – радиус окружности в пикселях.
//*******************************************************************
void LPH8731_3C_MC60::drawCircle (char xcenter, char ycenter, char rad, int color)
{
  signed int tswitch, x1 = 0, y1;
  char d;
  d = ycenter - xcenter;
  y1 = rad;
  tswitch = 3 - 2 * rad;
  while (x1 <= y1)
  {
    setPixColor(xcenter + x1, ycenter + y1, color);
    setPixColor(xcenter + x1, ycenter - y1, color);
    setPixColor(xcenter - x1, ycenter + y1, color);
    setPixColor(xcenter - x1, ycenter - y1, color);
    setPixColor(ycenter + y1 - d, ycenter + x1, color);
    setPixColor(ycenter + y1 - d, ycenter - x1, color);
    setPixColor(ycenter - y1 - d, ycenter + x1, color);
    setPixColor(ycenter - y1 - d, ycenter - x1, color);

    if (tswitch < 0) tswitch += (4 * x1 + 6);
    else
    {
      tswitch += (4 * (x1 - y1) + 10);
      y1--;
    }
    x1++;
  }
}    // LPH8731_3C_MC60


//*******************************************************************
//		Нарисовать круг, заполненный цветом color.
//*******************************************************************
void LPH8731_3C_MC60::fillCircle (char xcenter, char ycenter, char rad, int color)
{
  signed int x1 = 0, y1, tswitch;
  y1 = rad;
  tswitch = 1 - rad;

  do
  {
    drawLine(xcenter - x1, ycenter + y1, xcenter + x1, ycenter + y1, color);
    drawLine(xcenter - x1, ycenter - y1, xcenter + x1, ycenter - y1, color);
    drawLine(xcenter - y1, ycenter + x1, xcenter + y1, ycenter + x1, color);
    drawLine(xcenter - y1, ycenter - x1, xcenter + y1, ycenter - x1, color);

    if (tswitch < 0)
      tswitch += 3 + 2 * x1++;
    else
      tswitch += 5 + 2 * (x1++ - y1--);
  } while (x1 <= y1);
} // LPH8731_3C_MC60


//*******************************************************************
//                     Нарисовать контуры треугольника.
//*******************************************************************
void LPH8731_3C_MC60::drawTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 drawLine(x1, y1, x2, y2, color);
 drawLine(x3, y3, x1, y1, color);
 drawLine(x3, y3, x2, y2, color);  
} // LPH8731_3C_MC60


//*******************************************************************
//         Нарисовать треугольник, заполненный цветом color.
//*******************************************************************
void LPH8731_3C_MC60::fillTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 fillTriangleA(x1, y1, x2, y2, x3, y3, color);
 fillTriangleA(x3, y3, x1, y1, x2, y2, color);
 fillTriangleA(x3, y3, x2, y2, x1, y1, color);
}    // LPH8731_3C_MC60

//*******************************************************************
//		вспомогательная функцция для fillTriangle
//*******************************************************************
void LPH8731_3C_MC60::fillTriangleA(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
  signed long x, y, addx, dx, dy;
  signed long P;
  int i;
  long a1, a2, b1, b2;
  if (y1 > y2)  {
    b1 = y2;
    b2 = y1;
    a1 = x2;
    a2 = x1;
  }
  else  {
    b1 = y1;
    b2 = y2;
    a1 = x1;
    a2 = x2;
  }
  dx = a2 - a1;
  dy = b2 - b1;
  if (dx < 0)dx = -dx;
  if (dy < 0)dy = -dy;
  x = a1;
  y = b1;

  if (a1 > a2)    addx = -1;
  else           addx = 1;

  if (dx >= dy)
  {
    P = 2 * dy - dx;
    for (i = 0; i <= dx; ++i)
    {
      drawLine((int)x, (int)y, x3, y3, color);
      if (P < 0)
      {
        P += 2 * dy;
        x += addx;
      }
      else
      {
        P += 2 * dy - 2 * dx;
        x += addx;
        y ++;
      }
    }
  }
  else
  {
    P = 2 * dx - dy;
    for (i = 0; i <= dy; ++i)
    {
      drawLine((int)x, (int)y, x3, y3, color);
      if (P < 0)
      {
        P += 2 * dx;
        y ++;
      }
      else
      {
        P += 2 * dx - 2 * dy;
        x += addx;
        y ++;
      }
    }
  }
} // LPH8731_3C_MC60
