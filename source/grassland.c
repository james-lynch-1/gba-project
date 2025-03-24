
//{{BLOCK(grassland)

//======================================================================
//
//	grassland, 512x512@4, 
//	+ palette 11 entries, not compressed
//	+ 17 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 22 + 544 + 8192 = 8758
//
//	Time-stamp: 2025-02-25, 23:32:44
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#include "graphics/maps/grassland.h"

const unsigned short grasslandTiles[272] __attribute__((aligned(4))) =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x1000,0x0000,0x1100,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x1000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,0x0000,0x0010,
	0x0000,0x0010,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,
	0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,

	0x1100,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1000,0x1001,0x1111,0x1111,0x1115,0x5111,0x5515,0x5511,
	0x1000,0x0001,0x0000,0x0011,0x0000,0x0000,0x0000,0x0000,
	0x0111,0x1100,0x1111,0x1111,0x1111,0x5111,0x5511,0x5515,
	0x6669,0x6666,0x5566,0x5555,0x5686,0x5555,0x6856,0x5555,
	0x8556,0x5556,0x5556,0x5568,0x5556,0x5685,0x5556,0x6855,
	0x5556,0x6555,0x5556,0x8655,0x5556,0x5865,0x5556,0x5586,
	0x6556,0x5558,0x8656,0x5555,0x5866,0x5555,0x6669,0x6666,

	0x3333,0x3333,0x2223,0x2222,0x2223,0x2222,0x2223,0x2222,
	0x3333,0x3333,0x2222,0x2223,0x2222,0x2223,0x2222,0x2223,
	0x1110,0x1100,0x0010,0x0100,0x0000,0x0000,0x0000,0x0000,
	0x4440,0x4444,0x4404,0x4400,0x4444,0x4444,0x4444,0x7444,
	0x1100,0x1001,0x0000,0x0001,0x0000,0x0000,0x0000,0x0000,
	0x4000,0x0440,0x0404,0x4444,0x4444,0x4444,0x4447,0x4444,
	0x4447,0x4444,0x7444,0x4444,0x4444,0x7444,0x4444,0x7444,
	0x4444,0x4444,0x4444,0x4444,0x4744,0x4744,0x4444,0x4444,

	0x4444,0x7444,0x4444,0x7444,0x4444,0x4447,0x4444,0x4477,
	0x4444,0x4444,0x7444,0x4444,0x7444,0x4444,0x4444,0x4444,
	0x4444,0x4444,0x4744,0x7444,0x7777,0x7777,0x7777,0x7777,
	0x7744,0x7777,0x7444,0x4447,0x4444,0x4444,0x7777,0x4777,
	0x4444,0x4444,0x4447,0x4777,0x7777,0x7777,0x4477,0x4777,
	0x4477,0x4777,0x4444,0x4444,0x4444,0x4444,0x7477,0x7747,
	0x7774,0x7777,0x7744,0x7774,0x4444,0x4444,0x4444,0x7744,
	0x7777,0x7777,0x7777,0x7777,0x7444,0x4777,0x4444,0x4444,

	0x7777,0x7777,0x7477,0x4777,0x4444,0x4444,0x4444,0x4444,
	0x7777,0x7777,0x7777,0x7777,0x7444,0x4777,0x4444,0x4444,
};

const unsigned short grasslandMap[4096] __attribute__((aligned(4)))=
{
	0x0001,0x0002,0x0003,0x0003,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0003,0x0003,0x0003,0x0003,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,

	0x0004,0x0005,0x0003,0x0003,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0003,0x0003,0x0003,0x0003,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,

	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,

	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,

	0x0001,0x0002,0x0003,0x0003,0x0001,0x0002,0x0003,0x0003,
	0x0003,0x0003,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0006,0x0406,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0001,0x0002,0x0001,0x0002,0x0001,0x0002,

	0x0004,0x0005,0x0003,0x0003,0x0004,0x0005,0x0003,0x0003,
	0x0003,0x0003,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0007,0x0407,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0004,0x0005,0x0004,0x0005,0x0004,0x0005,

	0x0003,0x0003,0x0001,0x0002,0x0001,0x0002,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0001,0x0002,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0001,0x0002,

	0x0003,0x0003,0x0004,0x0005,0x0004,0x0005,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0004,0x0005,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0004,0x0005,

	0x0001,0x0002,0x0001,0x0002,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0004,0x0005,0x0004,0x0005,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0001,0x0002,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0004,0x0005,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0006,0x0406,0x0003,0x0003,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0007,0x0407,0x0003,0x0003,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0006,0x0406,0x0006,0x0406,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0007,0x0407,0x0007,0x0407,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,
	0x0006,0x0406,0x0003,0x0003,0x0006,0x0406,0x0006,0x0406,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,
	0x0007,0x0407,0x0003,0x0003,0x0007,0x0407,0x0007,0x0407,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0006,0x0406,0x0006,0x0406,0x0006,0x0406,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0007,0x0407,0x0007,0x0407,0x0007,0x0407,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,
	0x0006,0x0406,0x0006,0x0406,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,
	0x0007,0x0407,0x0007,0x0407,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,
	0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,
	0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,0x0008,0x0008,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0008,0x0008,
	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,
	0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0006,0x0406,0x0006,0x0406,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0007,0x0407,0x0007,0x0407,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0008,0x0008,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,

	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,

	0x0003,0x0003,0x0003,0x0003,0x0008,0x0008,0x0003,0x0003,
	0x0003,0x0003,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x0003,0x0003,
	0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,

	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,
	0x0009,0x000A,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x0009,0x000A,
	0x0009,0x000A,0x0009,0x000A,0x0009,0x000A,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,

	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,
	0x000B,0x000C,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000B,0x000C,
	0x000B,0x000C,0x000B,0x000C,0x000B,0x000C,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,

	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,

	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,

	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,

	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,

	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,
	0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,0x000D,0x000E,

	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
	0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,0x000F,0x0010,
};

const unsigned short grasslandPal[12] __attribute__((aligned(4))) =
{
	0x0A00,0x3FEB,0x4210,0x6739,0x0089,0x7F79,0x329B,0x0486,
	0x1D51,0x2529,0x0000,
};

CollisionTileRow512x512 grasslandColl[32] __attribute__((aligned(4))) =
{
	{.row = {1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1}},
	{.row = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1}},
	{.row = {1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,2,0,0,0,0,0,0,1,1,1}},
	{.row = {0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}},
	{.row = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0}},
	{.row = {0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,2,2,0,0,0,0}},
	{.row = {0,0,2,0,0,0,2,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0}},
	{.row = {0,0,0,2,2,2,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,7,7,0,7,7,7,0,0,0,0,7,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,7,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0}},
	{.row = {0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0}},
	{.row = {0,7,7,7,0,7,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,7,0,0,0,0,0,0,7,0,0,0}},
	{.row = {0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,0,0,7,7,0,0}},
	{.row = {0,7,0,7,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,0,0}},
	{.row = {0,7,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
	{.row = {0,0,7,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0,0,0,0,6,6,6,6,6,6,6,6,6}},
	{.row = {6,6,6,6,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,6,6,6,3,3,3,3,3,3,3,3,3}},
	{.row = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}},
	{.row = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}},
	{.row = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}}
};

//}}BLOCK(grassland)
