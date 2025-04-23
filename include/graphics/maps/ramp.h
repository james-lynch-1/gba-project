
//{{BLOCK(ramp)

//======================================================================
//
//	ramp, 256x256@4, 
//	+ palette 3 entries, not compressed
//	+ 4 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 6 + 128 + 2048 = 2182
//
//	Time-stamp: 2025-04-23, 17:08:32
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RAMP_H
#define GRIT_RAMP_H

#include "type.h"

#define rampTilesLen 128
extern const unsigned short rampTiles[64];

#define rampMapLen 2048
extern const unsigned short rampMap[1024];

#define rampPalLen 6
extern const unsigned short rampPal[4];

extern CollisionTileRow256x256 rampColl[32];

#endif // GRIT_RAMP_H

//}}BLOCK(ramp)
