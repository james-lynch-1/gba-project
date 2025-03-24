
//{{BLOCK(uglybig)

//======================================================================
//
//	uglybig, 1024x1024@4, 
//	+ palette 14 entries, not compressed
//	+ 17 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 128x128 
//	Total size: 28 + 544 + 32768 = 33340
//
//	Time-stamp: 2025-03-24, 15:24:43
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_UGLYBIG_H
#define GRIT_UGLYBIG_H

#include "entity.h"

#define uglybigTilesLen 544
extern const unsigned short uglybigTiles[272];

#define uglybigMapLen 32768
extern const unsigned short uglybigMap[16384];

#define uglybigPalLen 28
extern const unsigned short uglybigPal[14];

extern CollisionTileRow1024x1024 uglybigColl[64];
#endif // GRIT_UGLYBIG_H

//}}BLOCK(uglybig)
