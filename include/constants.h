#ifndef constantsh
#define constantsh

// animation state
#define ANIM_IDLE           0
#define ANIM_HURT           1
#define ANIM_WALK           2

// maximums (will change)
#define PLAYER_MAX_RADIUS   0x30000
#define PLAYER_DECAY_RATE   0x1000
#define MAX_ENTS            16
#define NUM_SCENES          3
#define ANGLE_MIN           0
#define ANGLE_MAX           65535
/** Player sprite width, in pixels */
#define PLAYER_SPR_WIDTH    32
/** Player sprite height, in pixels */
#define PLAYER_SPR_HEIGHT   32

/** Metatile width, in pixels */
#define MT_WIDTH            16
#define SBB_WIDTH_MT        16
#define MT_PER_SBB          256
#define TILE_WIDTH          8
#define SBB_WIDTH_T         32
#define SBB_HEIGHT_T        32
#define TILES_PER_SBB       1024

/** Size of packed collision data for a single metatile, in bits */
#define COLL_BITWIDTH       4

// SBB defines
/** Screen base block for bars (attack countdown/duration) layer */
#define UI_SBB              26
/** Screen base block for crosshair layer */
#define CHAIR_SBB           27
/** Screen base block for map layer */
#define MAP_SBB             31

#define CROSSHAIRS_X_MIN    8
#define CROSSHAIRS_X_MAX    SCR_W - 8
#define CROSSHAIRS_Y_MIN    8
#define CROSSHAIRS_Y_MAX    SCR_H - 8
#define CROSSHAIRS_SPEED    0x1C000

#define SPIN_WAIT_FRAMES    12
#define NUM_SPINPUTS        9

// crosshair-ent collision array indices
#define ATK_E_COLL          0
#define ATK_S_COLL          1
#define ATK_W_COLL          2
#define ATK_N_COLL          3
#define ATK_SE_COLL         4
#define ATK_SW_COLL         5
#define ATK_NW_COLL         6
#define ATK_NE_COLL         7
#define ATK_CTR_COLL        8
#define MAX_ATK_RANGE       9 // no. of elements in array (cardinals + quadrants + centre)

#endif
