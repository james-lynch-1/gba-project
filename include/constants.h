#ifndef constantsh
#define constantsh
/** Metatile width, in pixels */
#define MT_WIDTH            16
#define MT_PER_ROW_64x64    32
#define MT_PER_SBB_ROW      16
#define MT_PER_SBB          256

#define TILE_WIDTH          8
#define TILES_PER_ROW_64x64 64
#define TILES_PER_SBB_ROW   32
#define TILES_PER_SBB       1024
/** Map width, in pixels */
#define MAP_WIDTH_64x64     512
/** Map height, in pixels */
#define MAP_HEIGHT_64x64    512
/** Player sprite width, in pixels */
#define PLAYER_SPR_WIDTH    32
/** Player sprite height, in pixels */
#define PLAYER_SPR_HEIGHT   32
/** Size of packed collision data for a single metatile, in bits */
#define COLL_BITWIDTH       4

#define PLAYER_MAX_SPEED    0x30000
#define MAX_ENTS            16
#define MAX_ATK_RANGE       9

// SBB defines
/** Screen base block for bars (attack countdown/duration) layer */
#define BARS_SBB    26
/** Screen base block for crosshair layer */
#define CHAIR_SBB   27
/** Screen base block for map layer */
#define MAP_SBB     28

#define CROSSHAIRS_X_MIN    16
#define CROSSHAIRS_X_MAX    SCREEN_WIDTH - 16
#define CROSSHAIRS_Y_MIN    16
#define CROSSHAIRS_Y_MAX    SCREEN_HEIGHT - 16

#define SPIN_WAIT_FRAMES  12
#endif
