
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

#ifndef GRIT_HOME_H
#define GRIT_HOME_H

#include "entity.h"

#define homeTilesLen 672
extern const unsigned short homeTiles[336];

#define homeMapLen 2048
extern const unsigned short homeMap[1024];

#define homePalLen 26
extern const unsigned short homePal[14];

extern CollisionTileRow homeColl[16];

#endif // GRIT_HOME_H

//}}BLOCK(home)
