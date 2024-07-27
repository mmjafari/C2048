/*
Copyright (c) 2010-2021 <>< Charles Lohr, and several others!

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef _CNFG_C
#define _CNFG_C

#include "CNFG.h"

#ifndef CNFGHTTPSERVERONLY

#ifdef _CNFG_FANCYFONT
#include "TextTool/FontData.h"
#endif

//TODO: Refactor to remove malloc reliance.
#ifndef __clang__
#include <malloc.h>
#endif

int CNFGPenX, CNFGPenY;
uint32_t CNFGBGColor;
uint32_t CNFGLastColor;
//uint32_t CNFGDialogColor; //background for boxes [DEPRECATED]

// The following two arrays are generated by Fonter/fonter.cpp
const unsigned short RawdrawFontCharMap[256] = {
	65535, 0, 8, 16, 24, 31, 41, 50, 51, 65535, 65535, 57, 66, 65535, 75, 83,
	92, 96, 100, 108, 114, 123, 132, 137, 147, 152, 158, 163, 169, 172, 178, 182, 
	65535, 186, 189, 193, 201, 209, 217, 226, 228, 232, 236, 244, 248, 250, 252, 253, 
	255, 261, 266, 272, 278, 283, 289, 295, 300, 309, 316, 318, 321, 324, 328, 331, 
	337, 345, 352, 362, 368, 375, 382, 388, 396, 402, 408, 413, 422, 425, 430, 435, 
	442, 449, 458, 466, 472, 476, 480, 485, 492, 500, 507, 512, 516, 518, 522, 525, 
	527, 529, 536, 541, 546, 551, 557, 564, 572, 578, 581, 586, 593, 595, 604, 610, 
	615, 621, 627, 632, 638, 642, 648, 653, 660, 664, 670, 674, 680, 684, 690, 694, 
	65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 
	65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 
	700, 703, 711, 718, 731, 740, 744, 754, 756, 760, 766, 772, 775, 777, 785, 787, 
	792, 798, 803, 811, 813, 820, 827, 828, 831, 833, 838, 844, 853, 862, 874, 880, 
	889, 898, 908, 919, 928, 939, 951, 960, 969, 978, 988, 997, 1005, 1013, 1022, 1030,
	1039, 1047, 1054, 1061, 1070, 1079, 1086, 1090, 1099, 1105, 1111, 1118, 1124, 1133, 1140, 1150,
	1159, 1168, 1178, 1189, 1198, 1209, 1222, 1231, 1239, 1247, 1256, 1264, 1268, 1272, 1277, 1281,
	1290, 1300, 1307, 1314, 1322, 1331, 1338, 1342, 1349, 1357, 1365, 1374, 1382, 1390, 1397, 65535, };

const unsigned char RawdrawFontCharData[1405] = {
	0x00, 0x09, 0x20, 0x29, 0x03, 0x23, 0x14, 0x8b, 0x00, 0x09, 0x20, 0x29, 0x04, 0x24, 0x13, 0x8c, 
	0x01, 0x21, 0x23, 0x14, 0x03, 0x09, 0x11, 0x9a, 0x11, 0x22, 0x23, 0x14, 0x03, 0x02, 0x99, 0x01, 
	0x21, 0x23, 0x09, 0x03, 0x29, 0x03, 0x09, 0x12, 0x9c, 0x03, 0x2b, 0x13, 0x1c, 0x23, 0x22, 0x11, 
	0x02, 0x8b, 0x9a, 0x1a, 0x01, 0x21, 0x23, 0x03, 0x89, 0x03, 0x21, 0x2a, 0x21, 0x19, 0x03, 0x14, 
	0x23, 0x9a, 0x01, 0x10, 0x21, 0x12, 0x09, 0x12, 0x1c, 0x03, 0xab, 0x02, 0x03, 0x1b, 0x02, 0x1a, 
	0x13, 0x10, 0xa9, 0x01, 0x2b, 0x03, 0x29, 0x02, 0x11, 0x22, 0x13, 0x8a, 0x00, 0x22, 0x04, 0x88, 
	0x20, 0x02, 0x24, 0xa8, 0x01, 0x10, 0x29, 0x10, 0x14, 0x0b, 0x14, 0xab, 0x00, 0x0b, 0x0c, 0x20, 
	0x2b, 0xac, 0x00, 0x28, 0x00, 0x02, 0x2a, 0x10, 0x1c, 0x20, 0xac, 0x01, 0x21, 0x23, 0x03, 0x09, 
	0x20, 0x10, 0x14, 0x8c, 0x03, 0x23, 0x24, 0x04, 0x8b, 0x01, 0x10, 0x29, 0x10, 0x14, 0x0b, 0x14, 
	0x2b, 0x04, 0xac, 0x01, 0x18, 0x21, 0x10, 0x9c, 0x03, 0x1c, 0x23, 0x1c, 0x10, 0x9c, 0x02, 0x22, 
	0x19, 0x22, 0x9b, 0x02, 0x2a, 0x02, 0x19, 0x02, 0x9b, 0x01, 0x02, 0xaa, 0x02, 0x22, 0x11, 0x02, 
	0x13, 0xaa, 0x11, 0x22, 0x02, 0x99, 0x02, 0x13, 0x22, 0x8a, 0x10, 0x1b, 0x9c, 0x10, 0x09, 0x20, 
	0x99, 0x10, 0x1c, 0x20, 0x2c, 0x01, 0x29, 0x03, 0xab, 0x21, 0x10, 0x01, 0x23, 0x14, 0x0b, 0x10, 
	0x9c, 0x00, 0x09, 0x23, 0x2c, 0x04, 0x03, 0x21, 0xa8, 0x21, 0x10, 0x01, 0x12, 0x03, 0x14, 0x2b, 
	0x02, 0xac, 0x10, 0x99, 0x10, 0x01, 0x03, 0x9c, 0x10, 0x21, 0x23, 0x9c, 0x01, 0x2b, 0x11, 0x1b, 
	0x21, 0x0b, 0x02, 0xaa, 0x02, 0x2a, 0x11, 0x9b, 0x04, 0x9b, 0x02, 0xaa, 0x9c, 0x03, 0xa9, 0x00, 
	0x20, 0x24, 0x04, 0x08, 0x9a, 0x01, 0x10, 0x1c, 0x04, 0xac, 0x01, 0x10, 0x21, 0x22, 0x04, 0xac, 
	0x00, 0x20, 0x24, 0x0c, 0x12, 0xaa, 0x00, 0x02, 0x2a, 0x20, 0xac, 0x20, 0x00, 0x02, 0x22, 0x24, 
	0x8c, 0x20, 0x02, 0x22, 0x24, 0x04, 0x8a, 0x00, 0x20, 0x21, 0x12, 0x9c, 0x00, 0x0c, 0x00, 0x20, 
	0x2c, 0x04, 0x2c, 0x02, 0xaa, 0x00, 0x02, 0x22, 0x20, 0x08, 0x22, 0x8c, 0x19, 0x9b, 0x19, 0x13, 
	0x8c, 0x20, 0x02, 0xac, 0x01, 0x29, 0x03, 0xab, 0x00, 0x22, 0x8c, 0x01, 0x10, 0x21, 0x12, 0x1b, 
	0x9c, 0x21, 0x01, 0x04, 0x24, 0x22, 0x12, 0x13, 0xab, 0x04, 0x01, 0x10, 0x21, 0x2c, 0x02, 0xaa, 
	0x00, 0x04, 0x14, 0x23, 0x12, 0x0a, 0x12, 0x21, 0x10, 0x88, 0x23, 0x14, 0x03, 0x01, 0x10, 0xa9, 
	0x00, 0x10, 0x21, 0x23, 0x14, 0x04, 0x88, 0x00, 0x04, 0x2c, 0x00, 0x28, 0x02, 0x9a, 0x00, 0x0c, 
	0x00, 0x28, 0x02, 0x9a, 0x21, 0x10, 0x01, 0x03, 0x14, 0x23, 0x22, 0x9a, 0x00, 0x0c, 0x20, 0x2c, 
	0x02, 0xaa, 0x00, 0x28, 0x10, 0x1c, 0x04, 0xac, 0x00, 0x20, 0x23, 0x14, 0x8b, 0x00, 0x0c, 0x02, 
	0x12, 0x21, 0x28, 0x12, 0x23, 0xac, 0x00, 0x04, 0xac, 0x04, 0x00, 0x11, 0x20, 0xac, 0x04, 0x00, 
	0x2a, 0x20, 0xac, 0x01, 0x10, 0x21, 0x23, 0x14, 0x03, 0x89, 0x00, 0x0c, 0x00, 0x10, 0x21, 0x12, 
	0x8a, 0x01, 0x10, 0x21, 0x23, 0x14, 0x03, 0x09, 0x04, 0x9b, 0x00, 0x0c, 0x00, 0x10, 0x21, 0x12, 
	0x02, 0xac, 0x21, 0x10, 0x01, 0x23, 0x14, 0x8b, 0x00, 0x28, 0x10, 0x9c, 0x00, 0x04, 0x24, 0xa8, 
	0x00, 0x03, 0x14, 0x23, 0xa8, 0x00, 0x04, 0x2c, 0x14, 0x1b, 0x24, 0xa8, 0x00, 0x01, 0x23, 0x2c, 
	0x04, 0x03, 0x21, 0xa8, 0x00, 0x01, 0x12, 0x1c, 0x12, 0x21, 0xa8, 0x00, 0x20, 0x02, 0x04, 0xac, 
	0x10, 0x00, 0x04, 0x9c, 0x01, 0xab, 0x10, 0x20, 0x24, 0x9c, 0x01, 0x10, 0xa9, 0x04, 0xac, 0x00, 
	0x99, 0x02, 0x04, 0x24, 0x2a, 0x23, 0x12, 0x8a, 0x00, 0x04, 0x24, 0x22, 0x8a, 0x24, 0x04, 0x03, 
	0x12, 0xaa, 0x20, 0x24, 0x04, 0x02, 0xaa, 0x24, 0x04, 0x02, 0x22, 0x23, 0x9b, 0x04, 0x09, 0x02, 
	0x1a, 0x01, 0x10, 0xa9, 0x23, 0x12, 0x03, 0x14, 0x23, 0x24, 0x15, 0x8c, 0x00, 0x0c, 0x03, 0x12, 
	0x23, 0xac, 0x19, 0x12, 0x9c, 0x2a, 0x23, 0x24, 0x15, 0x8c, 0x00, 0x0c, 0x03, 0x13, 0x2a, 0x13, 
	0xac, 0x10, 0x9c, 0x02, 0x0c, 0x02, 0x1b, 0x12, 0x1c, 0x12, 0x23, 0xac, 0x02, 0x0c, 0x03, 0x12, 
	0x23, 0xac, 0x02, 0x22, 0x24, 0x04, 0x8a, 0x02, 0x0d, 0x04, 0x24, 0x22, 0x8a, 0x02, 0x04, 0x2c, 
	0x25, 0x22, 0x8a, 0x02, 0x0c, 0x03, 0x12, 0xaa, 0x22, 0x02, 0x03, 0x23, 0x24, 0x8c, 0x11, 0x1c, 
	0x02, 0xaa, 0x02, 0x04, 0x14, 0x2b, 0x24, 0xaa, 0x02, 0x03, 0x14, 0x23, 0xaa, 0x02, 0x03, 0x14, 
	0x1a, 0x13, 0x24, 0xaa, 0x02, 0x2c, 0x04, 0xaa, 0x02, 0x03, 0x1c, 0x22, 0x23, 0x8d, 0x02, 0x22, 
	0x04, 0xac, 0x20, 0x10, 0x14, 0x2c, 0x12, 0x8a, 0x10, 0x19, 0x13, 0x9c, 0x00, 0x10, 0x14, 0x0c, 
	0x12, 0xaa, 0x01, 0x10, 0x11, 0xa8, 0x03, 0x04, 0x24, 0x23, 0x12, 0x8b, 0x18, 0x11, 0x9c, 0x21, 
	0x10, 0x01, 0x02, 0x13, 0x2a, 0x10, 0x9b, 0x11, 0x00, 0x04, 0x24, 0x2b, 0x02, 0x9a, 0x01, 0x0a, 
	0x11, 0x29, 0x22, 0x2b, 0x03, 0x1b, 0x02, 0x11, 0x22, 0x13, 0x8a, 0x00, 0x11, 0x28, 0x11, 0x1c, 
	0x02, 0x2a, 0x03, 0xab, 0x10, 0x1a, 0x13, 0x9d, 0x20, 0x00, 0x02, 0x11, 0x2a, 0x02, 0x13, 0x22, 
	0x24, 0x8c, 0x08, 0xa8, 0x20, 0x10, 0x11, 0xa9, 0x10, 0x29, 0x20, 0x21, 0x11, 0x98, 0x11, 0x02, 
	0x1b, 0x21, 0x12, 0xab, 0x01, 0x21, 0xaa, 0x12, 0xaa, 0x10, 0x20, 0x21, 0x19, 0x12, 0x18, 0x11, 
	0xaa, 0x00, 0xa8, 0x01, 0x10, 0x21, 0x12, 0x89, 0x02, 0x2a, 0x11, 0x1b, 0x03, 0xab, 0x01, 0x10, 
	0x21, 0x03, 0xab, 0x01, 0x10, 0x21, 0x12, 0x0a, 0x12, 0x23, 0x8b, 0x11, 0xa8, 0x02, 0x0d, 0x04, 
	0x14, 0x2b, 0x22, 0xac, 0x14, 0x10, 0x01, 0x1a, 0x10, 0x20, 0xac, 0x9a, 0x14, 0x15, 0x8d, 0x20, 
	0xa9, 0x10, 0x20, 0x21, 0x11, 0x98, 0x01, 0x12, 0x0b, 0x11, 0x22, 0x9b, 0x00, 0x09, 0x02, 0x28, 
	0x12, 0x13, 0x2b, 0x22, 0xac, 0x00, 0x09, 0x02, 0x28, 0x12, 0x22, 0x13, 0x14, 0xac, 0x00, 0x10, 
	0x11, 0x09, 0x11, 0x02, 0x28, 0x12, 0x13, 0x2b, 0x22, 0xac, 0x18, 0x11, 0x12, 0x03, 0x14, 0xab, 
	0x04, 0x02, 0x11, 0x22, 0x2c, 0x03, 0x2b, 0x10, 0xa9, 0x04, 0x02, 0x11, 0x22, 0x2c, 0x03, 0x2b, 
	0x01, 0x98, 0x04, 0x02, 0x11, 0x22, 0x2c, 0x03, 0x2b, 0x01, 0x10, 0xa9, 0x04, 0x02, 0x11, 0x22, 
	0x2c, 0x03, 0x2b, 0x01, 0x10, 0x11, 0xa8, 0x04, 0x02, 0x11, 0x22, 0x2c, 0x03, 0x2b, 0x08, 0xa8, 
	0x04, 0x02, 0x11, 0x22, 0x2c, 0x03, 0x2b, 0x00, 0x20, 0x11, 0x88, 0x00, 0x0c, 0x02, 0x2a, 0x00, 
	0x19, 0x10, 0x1c, 0x10, 0x28, 0x14, 0xac, 0x23, 0x14, 0x03, 0x01, 0x10, 0x29, 0x14, 0x15, 0x8d, 
	0x02, 0x2a, 0x02, 0x04, 0x2c, 0x03, 0x1b, 0x00, 0x99, 0x02, 0x2a, 0x02, 0x04, 0x2c, 0x03, 0x1b, 
	0x11, 0xa8, 0x02, 0x2a, 0x02, 0x04, 0x2c, 0x03, 0x1b, 0x01, 0x10, 0xa9, 0x02, 0x2a, 0x02, 0x04, 
	0x2c, 0x03, 0x1b, 0x08, 0xa8, 0x02, 0x2a, 0x12, 0x1c, 0x04, 0x2c, 0x00, 0x99, 0x02, 0x2a, 0x12, 
	0x1c, 0x04, 0x2c, 0x11, 0xa8, 0x02, 0x2a, 0x12, 0x1c, 0x04, 0x2c, 0x01, 0x10, 0xa9, 0x02, 0x2a, 
	0x12, 0x1c, 0x04, 0x2c, 0x28, 0x88, 0x00, 0x10, 0x21, 0x23, 0x14, 0x04, 0x08, 0x02, 0x9a, 0x04, 
	0x02, 0x24, 0x2a, 0x01, 0x10, 0x11, 0xa8, 0x02, 0x22, 0x24, 0x04, 0x0a, 0x00, 0x99, 0x02, 0x22, 
	0x24, 0x04, 0x0a, 0x11, 0xa8, 0x02, 0x22, 0x24, 0x04, 0x0a, 0x11, 0x28, 0x00, 0x99, 0x02, 0x22, 
	0x24, 0x04, 0x0a, 0x01, 0x10, 0x11, 0xa8, 0x01, 0x21, 0x24, 0x04, 0x09, 0x08, 0xa8, 0x01, 0x2b, 
	0x03, 0xa9, 0x01, 0x10, 0x21, 0x23, 0x14, 0x03, 0x09, 0x03, 0xa9, 0x01, 0x04, 0x24, 0x29, 0x11, 
	0xa8, 0x01, 0x04, 0x24, 0x29, 0x00, 0x99, 0x02, 0x04, 0x24, 0x2a, 0x01, 0x10, 0xa9, 0x01, 0x04, 
	0x24, 0x29, 0x08, 0xa8, 0x01, 0x02, 0x13, 0x1c, 0x13, 0x22, 0x29, 0x11, 0xa8, 0x00, 0x0c, 0x01, 
	0x11, 0x22, 0x13, 0x8b, 0x00, 0x0d, 0x00, 0x10, 0x21, 0x1a, 0x02, 0x22, 0x24, 0x8c, 0x02, 0x04, 
	0x24, 0x2a, 0x23, 0x12, 0x0a, 0x00, 0x99, 0x02, 0x04, 0x24, 0x2a, 0x23, 0x12, 0x0a, 0x11, 0xa8, 
	0x02, 0x04, 0x24, 0x2a, 0x23, 0x12, 0x0a, 0x01, 0x10, 0xa9, 0x02, 0x04, 0x24, 0x2a, 0x23, 0x12, 
	0x0a, 0x01, 0x10, 0x11, 0xa8, 0x02, 0x04, 0x24, 0x2a, 0x23, 0x12, 0x0a, 0x09, 0xa9, 0x02, 0x04, 
	0x24, 0x2a, 0x23, 0x12, 0x0a, 0x01, 0x10, 0x21, 0x89, 0x02, 0x1b, 0x02, 0x04, 0x2c, 0x12, 0x1c, 
	0x12, 0x2a, 0x13, 0x2b, 0x22, 0xab, 0x03, 0x04, 0x2c, 0x03, 0x12, 0x2a, 0x14, 0x15, 0x8d, 0x24, 
	0x04, 0x02, 0x22, 0x23, 0x1b, 0x00, 0x99, 0x24, 0x04, 0x02, 0x22, 0x23, 0x1b, 0x11, 0xa8, 0x24, 
	0x04, 0x02, 0x22, 0x23, 0x1b, 0x01, 0x10, 0xa9, 0x24, 0x04, 0x02, 0x22, 0x23, 0x1b, 0x09, 0xa9, 
	0x12, 0x1c, 0x00, 0x99, 0x12, 0x1c, 0x11, 0xa8, 0x12, 0x1c, 0x01, 0x10, 0xa9, 0x12, 0x1c, 0x09, 
	0xa9, 0x00, 0x2a, 0x11, 0x28, 0x02, 0x22, 0x24, 0x04, 0x8a, 0x02, 0x0c, 0x03, 0x12, 0x23, 0x2c, 
	0x01, 0x10, 0x11, 0xa8, 0x02, 0x04, 0x24, 0x22, 0x0a, 0x00, 0x99, 0x02, 0x04, 0x24, 0x22, 0x0a, 
	0x11, 0xa8, 0x02, 0x04, 0x24, 0x22, 0x0a, 0x01, 0x10, 0xa9, 0x02, 0x04, 0x24, 0x22, 0x0a, 0x01, 
	0x10, 0x11, 0xa8, 0x02, 0x04, 0x24, 0x22, 0x0a, 0x09, 0xa9, 0x19, 0x02, 0x2a, 0x9b, 0x02, 0x04, 
	0x24, 0x22, 0x0a, 0x04, 0xaa, 0x02, 0x04, 0x14, 0x2b, 0x24, 0x2a, 0x00, 0x99, 0x02, 0x04, 0x14, 
	0x2b, 0x24, 0x2a, 0x11, 0xa8, 0x02, 0x04, 0x14, 0x2b, 0x24, 0x2a, 0x01, 0x10, 0xa9, 0x02, 0x04, 
	0x14, 0x2b, 0x24, 0x2a, 0x09, 0xa9, 0x02, 0x03, 0x1c, 0x22, 0x23, 0x0d, 0x11, 0xa8, 0x00, 0x0c, 
	0x02, 0x11, 0x22, 0x13, 0x8a, 0x02, 0x03, 0x1c, 0x22, 0x23, 0x0d, 0x09, 0xa9, };



//Set this if you are only using CNFG to create an OpenGL context.
#ifndef CNFGCONTEXTONLY
uint32_t CNFGDialogColor;

void CNFGDrawBox( short x1, short y1, short x2, short y2 )
{
	uint32_t lc = CNFGLastColor;
	CNFGColor( CNFGDialogColor );
	CNFGTackRectangle( x1, y1, x2, y2 );
	CNFGColor( lc );
	CNFGTackSegment( x1, y1, x2, y1 );
	CNFGTackSegment( x2, y1, x2, y2 );
	CNFGTackSegment( x2, y2, x1, y2 );
	CNFGTackSegment( x1, y2, x1, y1 );
}

void CNFGDrawText( const char * text, short scale )
{
	const unsigned char * lmap;
	float iox = (float)CNFGPenX; //x offset
	float ioy = (float)CNFGPenY; //y offset

	int drawPlace = 0;
	unsigned short index;
	int bQuit = 0;
	while( text[drawPlace] )
	{
		unsigned char c = text[drawPlace];
		switch( c )
		{
		case 9: // tab
			iox += 12 * scale;
			break;
		case 10: // linefeed
			iox = (float)CNFGPenX;
			ioy += 6 * scale;
			break;
		default:
			index = RawdrawFontCharMap[c];
			if( index == 65535 )
			{
				iox += 3 * scale;
				break;
			}

			lmap = &RawdrawFontCharData[index];
			short penx = 0, peny = 0;
			unsigned char start_seg = 1;
			do
			{
				unsigned char data = (*(lmap++));
				short x1 = (short)(((data >> 4) & 0x07)*scale + iox);
				short y1 = (short)((data        & 0x07)*scale + ioy);
				if( start_seg )
				{
					penx = x1;
					peny = y1;
					start_seg = 0;
					if( data & 0x08 )
						CNFGTackPixel( x1, y1 );
				}
				else
				{
					CNFGTackSegment( penx, peny, x1, y1 );
					penx = x1;
					peny = y1;
				}
				if( data & 0x08 ) start_seg = 1;
				bQuit = data & 0x80;
			} while( !bQuit );

			iox += 3 * scale;
		}
		drawPlace++;
	}
}

#ifndef FONT_CREATION_TOOL
#ifdef _CNFG_FANCYFONT

void CNFGDrawNiceText(const char* text, short scale)
{
	const unsigned char* lmap;
	float iox = (float)CNFGPenX; //x offset
	float ioy = (float)CNFGPenY; //y offset

	int place = 0;
	unsigned short index;
	int bQuit = 0;
	int segmentEnd = 0;
	while (text[place]) {
		unsigned char c = text[place];
		switch (c)
		{
		case 9: // tab
			iox += 16 * scale;
			break;
		case 10: // linefeed
			iox = (float)CNFGPenX;
			ioy += 6 * scale;
			break;
		default:
			index = CharIndex[c];
			if (index == 0) {
				iox += 4 * scale;
				break;
			}

			lmap = &FontData[index];

			short charWidth = ((*lmap) & 0xE0) >> 5; //0b11100000
			short xbase = ((*lmap) & 0x18) >> 3; //0b00011000
			short ybase = (*lmap) & 0x07; //0b00000111
			lmap++;
			do {

				int x1 = ((((*lmap) & 0x38) >> 3) * scale + iox + xbase * scale); //0b00111000
				int y1 = (((*lmap) & 0x07) * scale + ioy + ybase * scale);
				segmentEnd = *lmap & 0x40;
				int x2 = 0;
				int y2 = 0;
				lmap++;
				if (segmentEnd) {
					x2 = x1;
					y2 = y1;
				}
				else {

					x2 = ((((*lmap) & 0x38) >> 3) * scale + iox + xbase * scale);
					y2 = (((*lmap) & 0x07) * scale + ioy + ybase * scale);

				}


				CNFGTackSegment(x1, y1, x2, y2);
				bQuit = *(lmap - 1) & 0x80;

			} while (!bQuit);
			iox += (charWidth + 2) * scale;
			//iox += 8 * scale;
		}
		place++;
	}
}
#endif
#endif

void CNFGGetTextExtents( const char * text, int * w, int * h, int textsize )
{
	int charsx = 0;
	int charsy = 1;
	int charsline = 0;
	const char * s;

	for( s = text; *s; s++ )
	{
		if( *s == '\n' )
		{
			charsline = 0;
			if( *(s+1) )
				charsy++;
		}
		else
		{
			charsline++;
			if( charsline > charsx )
				charsx = charsline;
		}
	}

	*w = charsx * textsize * 3-1*textsize;
	*h = charsy * textsize * 6;
}

#if defined( CNFG_BATCH )

//This is the path by which we convert rawdraw functionality
//into nice batched triangle streams.

//Just FYI we use floats for geometry instead of shorts becase it is harder
//to triangularize a diagonal line int triangles with shorts and have it look good.
void CNFGEmitBackendTriangles( const float * fv, const uint32_t * col, int nr_verts );

//If on WASM, sqrtf is implied. On other platforms, need sqrtf from math.h
#ifdef __wasm__
float sqrtf( float f );
#define cnfg_sqrtf sqrtf
#elif defined( __TINYC__ ) && defined( WIN32 )
#define cnfg_sqrtf sqrt
#else
#define cnfg_sqrtf sqrtf
#include <math.h>
#endif

//Geometry batching system - so we can batch geometry and deliver it all at once.
float CNFGVertDataV[CNFG_BATCH*3];
uint32_t CNFGVertDataC[CNFG_BATCH];
int CNFGVertPlace;
static float wgl_last_width_over_2 = .5f;

static void EmitQuad( float cx0, float cy0, float cx1, float cy1, float cx2, float cy2, float cx3, float cy3 ) 
{
	//Because quads are really useful, but it's best to keep them all triangles if possible.
	//This lets us draw arbitrary quads.
	if( CNFGVertPlace >= CNFG_BATCH-6 ) CNFGFlushRender();
	float * fv = &CNFGVertDataV[CNFGVertPlace*3];
	fv[0] = cx0; fv[1] = cy0;
	fv[3] = cx1; fv[4] = cy1;
	fv[6] = cx2; fv[7] = cy2;
	fv[9] = cx2; fv[10] = cy2;
	fv[12] = cx1; fv[13] = cy1;
	fv[15] = cx3; fv[16] = cy3;
	uint32_t * col = &CNFGVertDataC[CNFGVertPlace];
	uint32_t color = CNFGLastColor;
	col[0] = color; col[1] = color; col[2] = color; col[3] = color; col[4] = color; col[5] = color;
	CNFGVertPlace += 6;
}


#if !defined( CNFGRASTERIZER ) && !defined( CNFGHTTP )

void CNFGTackPixel( short x1, short y1 )
{
	x1++; y1++;
	const float l2 = wgl_last_width_over_2;
	const float l2u = wgl_last_width_over_2+0.5f;
	EmitQuad( x1-l2u, y1-l2u, x1+l2, y1-l2u, x1-l2u, y1+l2, x1+l2, y1+l2 );
}


void CNFGTackSegment( short x1, short y1, short x2, short y2 )
{
	float ix1 = x1;
	float iy1 = y1;
	float ix2 = x2;
	float iy2 = y2;

	float dx = ix2-ix1;
	float dy = iy2-iy1;
	float imag = 1.f/(float)(cnfg_sqrtf(dx*dx+dy*dy));
	dx *= imag;
	dy *= imag;
	float orthox = dy*wgl_last_width_over_2;
	float orthoy =-dx*wgl_last_width_over_2;

	ix2 += dx/2 + 0.5f;
	iy2 += dy/2 + 0.5f;
	ix1 -= dx/2 - 0.5f;
	iy1 -= dy/2 - 0.5f;

	//This logic is incorrect. XXX FIXME.
	EmitQuad( (ix1 - orthox), (iy1 - orthoy), (ix1 + orthox), (iy1 + orthoy), (ix2 - orthox), (iy2 - orthoy), ( ix2 + orthox), ( iy2 + orthoy) );
}

void CNFGTackRectangle( short x1, short y1, short x2, short y2 )
{
	float ix1 = x1;
	float iy1 = y1;
	float ix2 = x2;
	float iy2 = y2;
	EmitQuad( ix1,iy1,ix2,iy1,ix1,iy2,ix2,iy2 );
}

void CNFGTackPoly( RDPoint * points, int verts )
{
	int i;
	int tris = verts-2;
	if( CNFGVertPlace >= CNFG_BATCH-tris*3 ) CNFGFlushRender();

	uint32_t color = CNFGLastColor;
	short * ptrsrc =  (short*)points;

	for( i = 0; i < tris; i++ )
	{
		float * fv = &CNFGVertDataV[CNFGVertPlace*3];
		fv[0] = ptrsrc[0];
		fv[1] = ptrsrc[1];
		fv[3] = ptrsrc[i*2+2];
		fv[4] = ptrsrc[i*2+3];
		fv[6] = ptrsrc[i*2+4];
		fv[7] = ptrsrc[i*2+5];

		uint32_t * col = &CNFGVertDataC[CNFGVertPlace];
		col[0] = color;
		col[1] = color;
		col[2] = color;

		CNFGVertPlace += 3;
	}
}

uint32_t CNFGColor( uint32_t RGB )
{
	return CNFGLastColor = RGB;
}

void	CNFGSetLineWidth( short width )
{
	wgl_last_width_over_2 = width/2.0f;// + 0.5;
}

#endif


#if !defined( __wasm__ ) && !defined( CNFGHTTP )
//In WASM, Javascript takes over this functionality.

//Shader compilation errors go to stderr.
#include <stdio.h>

#ifndef GL_VERTEX_SHADER
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_LINK_STATUS                    0x8B82
#define GL_TEXTURE_2D                     0x0DE1
#define GL_CLAMP_TO_EDGE                  0x812F
#define LGLchar char
#else
#define LGLchar GLchar
#endif

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#define CNFGOGL_NEED_EXTENSION
#include <GL/gl.h>
#endif

#ifdef  CNFGOGL_NEED_EXTENSION
// If we are going to be defining our own function pointer call
	#if defined(WINDOWS) || defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
	// Make sure to use __stdcall on Windows
		#define CHEWTYPEDEF( ret, name, rv, paramcall, ... ) \
			typedef ret (__stdcall *CNFGTYPE##name)( __VA_ARGS__ ); \
			ret (__stdcall *CNFG##name)( __VA_ARGS__ );
	#else
		#define CHEWTYPEDEF( ret, name, rv, paramcall, ... ) \
			typedef ret (*CNFGTYPE##name)( __VA_ARGS__ ); \
			ret (*CNFG##name)( __VA_ARGS__ );
	#endif
#else
//If we are going to be defining the real call
#define CHEWTYPEDEF( ret, name, rv, paramcall, ... ) \
	ret name (__VA_ARGS__);
#endif


#ifdef __cplusplus
extern "C" {
#endif

int (*MyFunc)( int program, const LGLchar *name );

CHEWTYPEDEF( GLint, glGetUniformLocation, return, (program,name), GLuint program, const LGLchar *name )
CHEWTYPEDEF( void, glEnableVertexAttribArray, , (index), GLuint index )
CHEWTYPEDEF( void, glUseProgram, , (program), GLuint program )
CHEWTYPEDEF( void, glGetProgramInfoLog, , (program,maxLength, length, infoLog), GLuint program, GLsizei maxLength, GLsizei *length, LGLchar *infoLog )
CHEWTYPEDEF( void, glGetProgramiv, , (program,pname,params), GLuint program, GLenum pname, GLint *params )
CHEWTYPEDEF( void, glBindAttribLocation, , (program,index,name), GLuint program, GLuint index, const LGLchar *name )
CHEWTYPEDEF( void, glGetShaderiv, , (shader,pname,params), GLuint shader, GLenum pname, GLint *params )
CHEWTYPEDEF( GLuint, glCreateShader, return, (e), GLenum e )
CHEWTYPEDEF( void, glVertexAttribPointer, , (index,size,type,normalized,stride,pointer), GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer )
CHEWTYPEDEF( void, glShaderSource, , (shader,count,string,length), GLuint shader, GLsizei count, const LGLchar *const*string, const GLint *length )
CHEWTYPEDEF( void, glAttachShader, , (program,shader), GLuint program, GLuint shader )
CHEWTYPEDEF( void, glCompileShader, ,(shader), GLuint shader )
CHEWTYPEDEF( void, glGetShaderInfoLog , , (shader,maxLength, length, infoLog), GLuint shader, GLsizei maxLength, GLsizei *length, LGLchar *infoLog )
CHEWTYPEDEF( GLuint, glCreateProgram, return, () , void )
CHEWTYPEDEF( void, glLinkProgram, , (program), GLuint program )
CHEWTYPEDEF( void, glDeleteShader, , (shader), GLuint shader )
CHEWTYPEDEF( void, glUniform4f, , (location,v0,v1,v2,v3), GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 )
CHEWTYPEDEF( void, glUniform1i, , (location,i0), GLint location, GLint i0 )
CHEWTYPEDEF( void, glActiveTexture, , (texture), GLenum texture )

#ifndef CNFGOGL_NEED_EXTENSION
#define CNFGglGetUniformLocation glGetUniformLocation
#define CNFGglEnableVertexAttribArray glEnableVertexAttribArray
#define CNFGglUseProgram glUseProgram
#define CNFGglEnableVertexAttribArray glEnableVertexAttribArray
#define CNFGglUseProgram glUseProgram
#define CNFGglGetProgramInfoLog glGetProgramInfoLog
#define CNFGglGetProgramiv glGetProgramiv
#define CNFGglShaderSource glShaderSource
#define CNFGglCreateShader glCreateShader
#define CNFGglAttachShader glAttachShader
#define CNFGglGetShaderiv glGetShaderiv
#define CNFGglCompileShader glCompileShader
#define CNFGglGetShaderInfoLog glGetShaderInfoLog
#define CNFGglCreateProgram glCreateProgram
#define CNFGglLinkProgram glLinkProgram
#define CNFGglDeleteShader glDeleteShader
#define CNFGglUniform4f glUniform4f
#define CNFGglBindAttribLocation glBindAttribLocation
#define CNFGglVertexAttribPointer glVertexAttribPointer
#define CNFGglUniform1i glUniform1i
#define CNFGglActiveTexture glActiveTexture

#endif

#ifdef __cplusplus
};
#endif

#ifdef CNFGOGL_NEED_EXTENSION
#if defined( WIN32 ) || defined( WINDOWS ) || defined( WIN64 )

//From https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
void * CNFGGetProcAddress(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if(p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1) )
	{
		static HMODULE module;
		if( !module ) module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}
	// We were unable to load the required openGL function 
	if (!p) {
		fprintf(stderr,"[rawdraw][warn]: Unable to load openGL extension \"%s\"\n", name);
	}
	return p;
}

#else
#include <dlfcn.h>


void * CNFGGetProcAddress(const char *name)
{
	//Tricky use RTLD_NEXT first so we don't accidentally link against ourselves.
	void * v1 = dlsym( (void*)((intptr_t)-1) /*RTLD_NEXT = -1*/ /*RTLD_DEFAULT = 0*/, name );
	//printf( "%s = %p\n", name, v1 );
	if( !v1 ) v1 = dlsym( 0, name );
	return v1;
}

#endif

// Try and load openGL extension functions required for rawdraw
static void CNFGLoadExtensionsInternal()
{
	CNFGglGetUniformLocation = (CNFGTYPEglGetUniformLocation) CNFGGetProcAddress( "glGetUniformLocation" );
	CNFGglEnableVertexAttribArray = (CNFGTYPEglEnableVertexAttribArray)CNFGGetProcAddress( "glEnableVertexAttribArray" );
	CNFGglUseProgram = (CNFGTYPEglUseProgram)CNFGGetProcAddress( "glUseProgram" );
	CNFGglGetProgramInfoLog = (CNFGTYPEglGetProgramInfoLog)CNFGGetProcAddress( "glGetProgramInfoLog" );
	CNFGglBindAttribLocation = (CNFGTYPEglBindAttribLocation)CNFGGetProcAddress( "glBindAttribLocation" );
	CNFGglGetProgramiv = (CNFGTYPEglGetProgramiv)CNFGGetProcAddress( "glGetProgramiv" );
	CNFGglGetShaderiv = (CNFGTYPEglGetShaderiv)CNFGGetProcAddress( "glGetShaderiv" );
	CNFGglVertexAttribPointer = (CNFGTYPEglVertexAttribPointer)CNFGGetProcAddress( "glVertexAttribPointer" );
	CNFGglCreateShader = (CNFGTYPEglCreateShader)CNFGGetProcAddress( "glCreateShader" );
	CNFGglShaderSource = (CNFGTYPEglShaderSource)CNFGGetProcAddress( "glShaderSource" );
	CNFGglAttachShader = (CNFGTYPEglAttachShader)CNFGGetProcAddress( "glAttachShader" );
	CNFGglCompileShader = (CNFGTYPEglCompileShader)CNFGGetProcAddress( "glCompileShader" );
	CNFGglGetShaderInfoLog = (CNFGTYPEglGetShaderInfoLog)CNFGGetProcAddress( "glGetShaderInfoLog" );
	CNFGglDeleteShader = (CNFGTYPEglDeleteShader)CNFGGetProcAddress( "glDeleteShader" );
	CNFGglLinkProgram = (CNFGTYPEglLinkProgram)CNFGGetProcAddress( "glLinkProgram" );
	CNFGglCreateProgram = (CNFGTYPEglCreateProgram)CNFGGetProcAddress( "glCreateProgram" );
	CNFGglUniform4f = (CNFGTYPEglUniform4f)CNFGGetProcAddress( "glUniform4f" );
	CNFGglUniform1i = (CNFGTYPEglUniform1i)CNFGGetProcAddress( "glUniform1i" );
	CNFGglActiveTexture = (CNFGTYPEglActiveTexture)CNFGGetProcAddress("glActiveTexture");

	// Check if any of these functions didn't get loaded
	uint8_t not_all_functions_loaded = 
		!CNFGglGetUniformLocation  || !CNFGglEnableVertexAttribArray || !CNFGglUseProgram       ||
		!CNFGglGetProgramInfoLog   || !CNFGglBindAttribLocation      || !CNFGglGetProgramiv     ||
		!CNFGglVertexAttribPointer || !CNFGglCreateShader            || !CNFGglShaderSource     ||
		!CNFGglAttachShader        || !CNFGglCompileShader           || !CNFGglGetShaderInfoLog ||
		!CNFGglDeleteShader        || !CNFGglLinkProgram             || !CNFGglCreateProgram    ||
		!CNFGglUniform4f           || !CNFGglUniform1i               || !CNFGglActiveTexture; 
	if (not_all_functions_loaded) {
		fprintf(
			stderr,
			"[rawdraw][err]: Unable to load all openGL extensions required for rawdraw\n"
			"\tPlease update your graphics drivers or unexpected crashes may occur.\n"
		);
	}

	// Give a very stern warning if unable to create or compile shaders
	if (!CNFGglCreateShader || !CNFGglCompileShader) {
		fprintf(
			stderr,
			"[rawdraw][err]: Unable to create or compile shaders, this will cause a fatal error if "
			"openGL is used.\n"
			"\tUpdate your video graphics drivers or switch to software graphics.\n"
		);
	}
}
#else
static void CNFGLoadExtensionsInternal() { }
#endif



GLuint gRDShaderProg = -1;
GLuint gRDBlitProg = -1;
GLuint gRDShaderProgUX = -1;
GLuint gRDBlitProgUX = -1;
GLuint gRDBlitProgUT = -1;
GLuint gRDBlitProgTex = -1;
GLuint gRDLastResizeW;
GLuint gRDLastResizeH;


GLuint CNFGGLInternalLoadShader( const char * vertex_shader, const char * fragment_shader )
{
	GLuint fragment_shader_object = 0;
	GLuint vertex_shader_object = 0;
	GLuint program = 0;
	int ret;

	vertex_shader_object = CNFGglCreateShader(GL_VERTEX_SHADER);
	if (!vertex_shader_object) {
		fprintf( stderr, "Error: glCreateShader(GL_VERTEX_SHADER) "
			"failed: 0x%08X\n", glGetError());
		goto fail;
	}

	CNFGglShaderSource(vertex_shader_object, 1, &vertex_shader, NULL);
	CNFGglCompileShader(vertex_shader_object);

	CNFGglGetShaderiv(vertex_shader_object, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		fprintf( stderr,"Error: vertex shader compilation failed!\n");
		CNFGglGetShaderiv(vertex_shader_object, GL_INFO_LOG_LENGTH, &ret);

		if (ret > 1) {
			//TODO: Refactor to remove malloc reliance.
			#ifndef __clang__
			char * log = (char*)alloca(ret);
			CNFGglGetShaderInfoLog(vertex_shader_object, ret, NULL, log);
			fprintf( stderr, "%s", log);
			#endif
		}
		goto fail;
	}

	fragment_shader_object = CNFGglCreateShader(GL_FRAGMENT_SHADER);
	if (!fragment_shader_object) {
		fprintf( stderr, "Error: glCreateShader(GL_FRAGMENT_SHADER) "
			"failed: 0x%08X\n", glGetError());
		goto fail;
	}

	CNFGglShaderSource(fragment_shader_object, 1, &fragment_shader, NULL);
	CNFGglCompileShader(fragment_shader_object);

	CNFGglGetShaderiv(fragment_shader_object, GL_COMPILE_STATUS, &ret);
	if (!ret) {
		fprintf( stderr, "Error: fragment shader compilation failed!\n");
		CNFGglGetShaderiv(fragment_shader_object, GL_INFO_LOG_LENGTH, &ret);

		if (ret > 1) {
			//TODO: Refactor to remove malloc reliance.
			#ifndef __clang__
			char * log = (char*)malloc(ret);
			CNFGglGetShaderInfoLog(fragment_shader_object, ret, NULL, log);
			fprintf( stderr, "%s", log);
			free( log );
			#endif
		}
		goto fail;
	}

	program = CNFGglCreateProgram();
	if (!program) {
		fprintf( stderr, "Error: failed to create program!\n");
		goto fail;
	}

	CNFGglAttachShader(program, vertex_shader_object);
	CNFGglAttachShader(program, fragment_shader_object);

	CNFGglBindAttribLocation(program, 0, "a0");
	CNFGglBindAttribLocation(program, 1, "a1");

	CNFGglLinkProgram(program);

	CNFGglGetProgramiv(program, GL_LINK_STATUS, &ret);
	if (!ret) {
		fprintf( stderr, "Error: program linking failed!\n");
		CNFGglGetProgramiv(program, GL_INFO_LOG_LENGTH, &ret);

		if (ret > 1) {
			//TODO: Refactor to remove malloc reliance.
			#ifndef __clang__
			char *log = (char*)alloca(ret);
			CNFGglGetProgramInfoLog(program, ret, NULL, log);
			fprintf( stderr, "%s", log);
			#endif
		}
		goto fail;
	}
	return program;
fail:
	if( !vertex_shader_object ) CNFGglDeleteShader( vertex_shader_object );
	if( !fragment_shader_object ) CNFGglDeleteShader( fragment_shader_object );
	if( !program ) CNFGglDeleteShader( program );
	return -1;
}

#if defined( CNFGEWGL ) && !defined( CNFG_NO_PRECISION )
#define PRECISIONA "lowp"
#define PRECISIONB "mediump"
#else
#define PRECISIONA
#define PRECISIONB
#endif

void CNFGSetupBatchInternal()
{
	short w, h;

	CNFGLoadExtensionsInternal();

	CNFGGetDimensions( &w, &h );

	gRDShaderProg = CNFGGLInternalLoadShader(
		"uniform vec4 xfrm;"
		"attribute vec3 a0;"
		"attribute vec4 a1;"
		"varying " PRECISIONA " vec4 vc;"
		"void main() { gl_Position = vec4( a0.xy*xfrm.xy+xfrm.zw, a0.z, 0.5 ); vc = a1; }",

		"varying " PRECISIONA " vec4 vc;"
		"void main() { gl_FragColor = vec4(vc.abgr); }" 
	);

	CNFGglUseProgram( gRDShaderProg );
	gRDShaderProgUX = CNFGglGetUniformLocation ( gRDShaderProg , "xfrm" );


	gRDBlitProg = CNFGGLInternalLoadShader(
		"uniform vec4 xfrm;"
		"attribute vec3 a0;"
		"attribute vec4 a1;"
		"varying " PRECISIONB " vec2 tc;"
		"void main() { gl_Position = vec4( a0.xy*xfrm.xy+xfrm.zw, a0.z, 0.5 ); tc = a1.xy; }",
		
		"varying " PRECISIONB " vec2 tc;"
		"uniform sampler2D tex;"
		"void main() { gl_FragColor = texture2D(tex,tc)."

#if !defined( CNFGRASTERIZER )
"wzyx"
#else
"wxyz"
#endif
";}" 	);

	CNFGglUseProgram( gRDBlitProg );
	gRDBlitProgUX = CNFGglGetUniformLocation ( gRDBlitProg , "xfrm" );
	gRDBlitProgUT = CNFGglGetUniformLocation ( gRDBlitProg , "tex" );
	glGenTextures( 1, &gRDBlitProgTex );

	CNFGglEnableVertexAttribArray(0);
	CNFGglEnableVertexAttribArray(1);

	glDisable(GL_DEPTH_TEST);
	glDepthMask( GL_FALSE );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	CNFGVertPlace = 0;
}

#ifndef CNFGRASTERIZER
void CNFGInternalResize(short x, short y)
#else
void CNFGInternalResizeOGLBACKEND(short x, short y)
#endif
{
	glViewport( 0, 0, x, y );
	gRDLastResizeW = x;
	gRDLastResizeH = y;
	if (gRDShaderProg == 0xFFFFFFFF) { return; } // Prevent trying to set uniform if the shader isn't ready yet.
	CNFGglUseProgram( gRDShaderProg );
	CNFGglUniform4f( gRDShaderProgUX, 1.f/x, -1.f/y, -0.5f, 0.5f);
}

void	CNFGEmitBackendTriangles( const float * vertices, const uint32_t * colors, int num_vertices )
{
	CNFGglUseProgram( gRDShaderProg );
	CNFGglUniform4f( gRDShaderProgUX, 1.f/gRDLastResizeW, -1.f/gRDLastResizeH, -0.5f, 0.5f);
	CNFGglVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	CNFGglVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);
	glDrawArrays( GL_TRIANGLES, 0, num_vertices);
}


#ifdef CNFGOGL
// this is here, so people don't have to include opengl
void CNFGDeleteTex( unsigned int tex )
{
	glDeleteTextures(1, &tex);
}

unsigned int CNFGTexImage( uint32_t *data, int w, int h )
{
	GLuint tex;

	glGenTextures(1, &tex);
	glEnable( GL_TEXTURE_2D );
	CNFGglActiveTexture( 0 );
	glBindTexture( GL_TEXTURE_2D, tex );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,  GL_RGBA,
		GL_UNSIGNED_BYTE, data );

	return (unsigned int)tex;
}

void CNFGBlitTex( unsigned int tex, int x, int y, int w, int h )
{
	if( w == 0 || h == 0 ) return;

	CNFGFlushRender();

	CNFGglUseProgram( gRDBlitProg );
	CNFGglUniform4f( gRDBlitProgUX,
		1.f/gRDLastResizeW, -1.f/gRDLastResizeH,
		-0.5f+x/(float)gRDLastResizeW, 0.5f-y/(float)gRDLastResizeH );
	CNFGglUniform1i( gRDBlitProgUT, 0 );

	glBindTexture(GL_TEXTURE_2D, tex);

	const float verts[] = {
		0,0, (float)w,0, (float)w,(float)h,
		0,0, (float)w,(float)h, 0,(float)h, };
	static const uint8_t tex_verts[] = {
		0,0,   255,0,  255,255,
		0,0,  255,255, 0,255 };

	CNFGglVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
	CNFGglVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_TRUE, 0, tex_verts);

	glDrawArrays( GL_TRIANGLES, 0, 6);
}
#endif

#ifdef CNFGRASTERIZER
void CNFGBlitImageInternal( uint32_t * data, int x, int y, int w, int h )
#else
void CNFGBlitImage( uint32_t * data, int x, int y, int w, int h )
#endif
{
	glEnable( GL_TEXTURE_2D );
	CNFGglActiveTexture( 0 );
	glBindTexture( GL_TEXTURE_2D, gRDBlitProgTex );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,  GL_RGBA,
		GL_UNSIGNED_BYTE, data );

	CNFGBlitTex( gRDBlitProgTex, x, y, w, h );
}

void CNFGUpdateScreenWithBitmap( uint32_t * data, int w, int h )
{
#ifdef CNFGRASTERIZER
	CNFGBlitImageInternal( data, 0, 0, w, h );
	void CNFGSwapBuffersInternal();
	CNFGSwapBuffersInternal();
#else
	CNFGBlitImage( data, 0, 0, w, h );
#endif
}

#ifndef CNFGRASTERIZER

void CNFGFlushRender()
{
	if( !CNFGVertPlace ) return;
	CNFGEmitBackendTriangles( CNFGVertDataV, CNFGVertDataC, CNFGVertPlace );
	CNFGVertPlace = 0;
}

void CNFGClearFrame()
{
	glClearColor( ((CNFGBGColor&0xff000000)>>24)/255.0f, 
		((CNFGBGColor&0xff0000)>>16)/255.0f,
		(CNFGBGColor&0xff00)/65280.0f,
		(CNFGBGColor&0xff)/255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

#endif

#endif //__wasm__

#else

void CNFGFlushRender() { }

#endif


#endif
#endif // CNFGHTTPSERVERONLY
#endif //_CNFG_C
