
//{{BLOCK(brin)

//======================================================================
//
//	brin, 512x512@4, 
//	+ palette 8 entries, not compressed
//	+ 35 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 16 + 1120 + 8192 = 9328
//
//	Time-stamp: 2025-01-16, 13:10:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================


#ifndef GRIT_BRIN_H
#define GRIT_BRIN_H

#include "entity.h"

#define brinTilesLen 1120
extern const unsigned short brinTiles[560];

#define brinMapLen 8192
extern const unsigned short brinMap[4096];

#define brinPalLen 16
extern const unsigned short brinPal[8];

// extern const unsigned short brinCollision[1024];

extern CollisionTileRow512x512 brinColl[32];

#endif // GRIT_BRIN_H

//}}BLOCK(brin)
