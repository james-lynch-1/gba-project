
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

#ifndef GRIT_GRASSLAND_H
#define GRIT_GRASSLAND_H

#include "type.h"

extern ActionTile GrasslandActionTiles[];

#define grasslandTilesLen 544
extern const unsigned short grasslandTiles[272];

#define grasslandMapLen 8192
extern const unsigned short grasslandMap[4096];

#define grasslandPalLen 22
extern const unsigned short grasslandPal[12];

extern CollisionTileRow512x512 grasslandColl[32];

#endif // GRIT_GRASSLAND_H

//}}BLOCK(grassland)
