
//{{BLOCK(home)

//======================================================================
//
//	home, 256x256@4, 
//	+ palette 13 entries, not compressed
//	+ 21 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 26 + 672 + 2048 = 2746
//
//	Time-stamp: 2025-03-04, 10:43:23
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#include "graphics/maps/home.h"

const unsigned short homeTiles[336] __attribute__((aligned(4))) =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x2222,0x2222,0x6662,0x6666,0x6662,0x6666,0x6662,0x6666,
	0x2222,0x2222,0x6666,0x6662,0x6666,0x6662,0x6666,0x6662,
	0x333B,0x3333,0x7733,0x7777,0x7353,0x7777,0x3573,0x7777,
	0x5773,0x7773,0x7773,0x7735,0x7773,0x7357,0x7773,0x3577,

	0x7773,0x3777,0x7773,0x5377,0x7773,0x7537,0x7773,0x7753,
	0x3773,0x7775,0x5373,0x7777,0x7533,0x7777,0x333B,0x3333,
	0x8888,0x8888,0x8888,0x8888,0x8AAA,0x8888,0x8888,0x8888,
	0x8888,0x8888,0x8888,0x8888,0xAA88,0xAAAA,0x8888,0x8888,
	0x8888,0x8888,0x8888,0x8888,0x8888,0xAAA8,0x8888,0x8888,
	0x8888,0x8888,0x8888,0x8888,0x8888,0x8888,0x8888,0x8888,
	0x8888,0x8888,0x8888,0x8888,0x8888,0x8888,0x8888,0x8888,
	0x8888,0x8888,0x8888,0x8888,0x8888,0xAA88,0x8888,0x8888,

	0x8888,0x8888,0x8888,0x8888,0xAAAA,0x88AA,0x8888,0x8888,
	0x8888,0x8888,0x8888,0x8888,0x88AA,0x8888,0x8888,0x8888,
	0x0000,0x0000,0x0000,0x0000,0x1000,0x0000,0x1100,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x1000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0000,0x0010,
	0x0000,0x0010,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1110,0x1100,0x0010,0x0100,0x0000,0x0000,0x0000,0x0000,
	0x4440,0x4444,0x4404,0x4400,0x4444,0x4444,0x4444,0x9444,

	0x1100,0x1001,0x0000,0x0001,0x0000,0x0000,0x0000,0x0000,
	0x4000,0x0440,0x0404,0x4444,0x4444,0x4444,0x4449,0x4444,
	0x1100,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1000,0x1001,0x1111,0x1111,0x1117,0x7111,0x7717,0x7711,
	0x1000,0x0001,0x0000,0x0011,0x0000,0x0000,0x0000,0x0000,
	0x0111,0x1100,0x1111,0x1111,0x1111,0x7111,0x7711,0x7717,
	0x4449,0x4444,0x9444,0x4444,0x4444,0x9444,0x4444,0x9444,
	0x4444,0x4444,0x4444,0x4444,0x4944,0x4944,0x4444,0x4444,

	0x4444,0x9444,0x4444,0x9444,0x4444,0x4449,0x4444,0x4499,
	0x4444,0x4444,0x9444,0x4444,0x9444,0x4444,0x4444,0x4444,
	0x4444,0x4444,0x4944,0x9444,0x9999,0x9999,0x9999,0x9999,
	0x9944,0x9999,0x9444,0x4449,0x4444,0x4444,0x9999,0x4999,
	0x4444,0x4444,0x4449,0x4999,0x9999,0x9999,0x4499,0x4999,
	0x4499,0x4999,0x4444,0x4444,0x4444,0x4444,0x9499,0x9949,
	0x9994,0x9999,0x9944,0x9994,0x4444,0x4444,0x4444,0x9944,
	0x9999,0x9999,0x9999,0x9999,0x9444,0x4999,0x4444,0x4444,

	0x9999,0x9999,0x9499,0x4999,0x4444,0x4444,0x4444,0x4444,
	0x9999,0x9999,0x9999,0x9999,0x9444,0x4999,0x4444,0x4444,
};

const unsigned short homeMap[1024] __attribute__((aligned(4))) =
{
	0x0001,0x0001,0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0003,0x0403,0x0003,0x0403,0x0003,0x0403,
	0x0003,0x0403,0x0003,0x0403,0x0003,0x0403,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0002,0x0002,0x0004,0x0404,0x0004,0x0404,0x0004,0x0404,
	0x0004,0x0404,0x0004,0x0404,0x0004,0x0404,0x0002,0x0002,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0003,0x0403,
	0x0005,0x0006,0x0003,0x0403,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0003,0x0403,0x0005,0x0006,0x0003,0x0403,
	0x0003,0x0403,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0002,0x0002,0x0004,0x0404,
	0x0007,0x0008,0x0004,0x0404,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0004,0x0404,0x0007,0x0008,0x0004,0x0404,
	0x0004,0x0404,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0003,0x0403,0x0003,0x0403,
	0x0003,0x0403,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0004,0x0404,0x0004,0x0404,
	0x0004,0x0404,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0002,0x0002,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0003,0x0403,
	0x0003,0x0403,0x0005,0x0006,0x0005,0x0006,0x0003,0x0403,
	0x0003,0x0403,0x0003,0x0403,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0002,0x0002,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0004,0x0404,
	0x0004,0x0404,0x0007,0x0008,0x0007,0x0008,0x0004,0x0404,
	0x0004,0x0404,0x0004,0x0404,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0003,0x0403,
	0x0003,0x0403,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0004,0x0404,
	0x0004,0x0404,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0002,0x0002,0x0001,0x0001,

	0x0001,0x0001,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,0x0003,0x0403,
	0x0003,0x0403,0x0005,0x0006,0x0005,0x0006,0x0005,0x0006,
	0x0005,0x0006,0x0003,0x0403,0x0002,0x0002,0x0001,0x0001,
	0x0001,0x0001,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,0x0004,0x0404,
	0x0004,0x0404,0x0007,0x0008,0x0007,0x0008,0x0007,0x0008,
	0x0007,0x0008,0x0004,0x0404,0x0002,0x0002,0x0001,0x0001,

	0x0009,0x000A,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x0009,0x000A,
	0x000D,0x000E,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000D,0x000E,

	0x0001,0x0001,0x0009,0x000A,0x0011,0x0012,0x0011,0x0012,
	0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,
	0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,
	0x0011,0x0012,0x0011,0x0012,0x0009,0x000A,0x0001,0x0001,
	0x0001,0x0001,0x000D,0x000E,0x0013,0x0014,0x0013,0x0014,
	0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,
	0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,
	0x0013,0x0014,0x0013,0x0014,0x000D,0x000E,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0009,0x000A,0x0011,0x0012,
	0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,
	0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,
	0x0011,0x0012,0x0009,0x000A,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x000D,0x000E,0x0013,0x0014,
	0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,
	0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,
	0x0013,0x0014,0x000D,0x000E,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0009,0x000A,
	0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,
	0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,0x0011,0x0012,
	0x0009,0x000A,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x000D,0x000E,
	0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,
	0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,0x0013,0x0014,
	0x000D,0x000E,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,

	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
};

const unsigned short homePal[14] __attribute__((aligned(4))) =
{
	0x0A00,0x3FEB,0x6739,0x329B,0x0089,0x1D51,0x4210,0x7F79,
	0x2EDF,0x0486,0x11B6,0x2529,0x0000,
};

CollisionTileRow256x256 homeColl[16] __attribute__((aligned(4))) =
{
	{.row = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0}},
	{.row = {0,1,1,1,1,2,2,2,2,2,2,1,1,1,1,0}},
	{.row = {0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0}},
	{.row = {0,1,1,2,0,2,0,0,0,2,0,2,2,1,1,0}},
	{.row = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0}},
	{.row = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0}},
	{.row = {0,1,2,2,2,0,0,0,0,0,0,0,0,0,1,0}},
	{.row = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0}},
	{.row = {0,1,0,0,0,0,0,2,2,0,0,2,2,2,1,0}},
	{.row = {0,0,0,0,0,0,0,2,2,0,0,0,0,0,1,0}},
	{.row = {0,0,0,0,0,0,0,2,2,0,0,0,0,2,1,0}},
	{.row = {4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4}},
	{.row = {0,4,6,6,6,6,6,6,6,6,6,6,6,6,4,0}},
	{.row = {0,0,4,6,6,6,6,6,6,6,6,6,6,4,0,0}},
	{.row = {0,0,0,4,6,6,6,6,6,6,6,6,4,0,0,0}},
	{.row = {0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0}}
};

//}}BLOCK(home)
