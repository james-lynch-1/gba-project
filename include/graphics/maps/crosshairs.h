
//{{BLOCK(crosshairs)

//======================================================================
//
//	crosshairs, 256x256@4, 
//	+ palette 4 entries, not compressed
//	+ 4 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 8 + 128 + 2048 = 2184
//
//	Time-stamp: 2025-03-07, 12:31:07
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CROSSHAIRS_H
#define GRIT_CROSSHAIRS_H

#define crosshairsTilesLen 128
extern const unsigned short crosshairsTiles[64];

#define crosshairsMapLen 2048
extern const unsigned short crosshairsMap[1024];

#define crosshairsPalLen 8
extern const unsigned short crosshairsPal[4];

#endif // GRIT_CROSSHAIRS_H

//}}BLOCK(crosshairs)
