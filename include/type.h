#ifndef typeh
#define typeh

#include <tonc.h>
#include <stdlib.h>
#include "constants.h"

// collision direction masks to get direction from a collision bitfield

#define X_CNTR_COLL_MASK    0x000000F0u
#define Y_CNTR_COLL_MASK    0x000F0000u
#define X_COLL_MASK         0x00000FFFu
#define Y_COLL_MASK         0x00FFF000u
#define X_CRNR_COLL_MASK    0x00000F0Fu
#define Y_CRNR_COLL_MASK    0x00F0F000u
#define X_CRNR_COLL_1_MASK  0x0000000Fu
#define X_CRNR_COLL_2_MASK  0x00000F00u
#define Y_CRNR_COLL_1_MASK  0x0000F000u
#define Y_CRNR_COLL_2_MASK  0x00F00000u

#define PACKED_COLLMAP_MASK 0x0000000Fu
#define CORNER_COLL_MASK    0x00F0FF0Fu
#define COLL_MASK           0xFFFFFFFFu

typedef enum {
    CHAR,
    DIRECTION,
    PTR,
    INT,
    INTHEX,
    U8,
    S16,
    S32,
    U16,
    U16HEX,
    U32,
    U32HEX,
    SPLITWORD,
    USPLITWORD
} Type;

enum ItemClass { // corresponds with atk array in attacks.c
    ITEM_BASICATK,
    ITEM_SCREENATK,
    ITEM_EASTATK,
    ITEM_SOUTHATK,
    ITEM_WESTATK,
    ITEM_NORTHATK,
    ITEM_SOUTHEASTATK,
    ITEM_SOUTHWESTATK,
    ITEM_NORTHWESTATK,
    ITEM_NORTHEASTATK,
    ITEM_CROSSATK
};

#define NUM_ITEMS   11

enum ActionClass {
    ADD_ITEM = 14,
    DO_ACTION = 15
};

enum AtkClass {
    DIRECT = 0, // fired by holding the attack button
    SPECIAL = 1 // fired by triggering some other way, has a fixed countdown and duration that cannot be interrupted
};

enum AtkId {
    BASICATK, SCREENATK,
    EATK, SATK, WATK, NATK,
    SEATK, SWATK, NWATK, NEATK,
    CATK
};

typedef enum GameStateEnum_ {
    NORMAL,
    TITLE,
    PAUSE
} GameStateEnum;

typedef struct State_ { // for entity states (HSM)
    struct State_* next;
    void (*enterAction)();
    void (*exitAction)();
    void (*handleAPress)();
    void (*handleBPress)();
    void (*handleDPadPress)();
    void (*handleLPress)();
    void (*handleRPress)();
    void (*handleStartPress)();
    void (*handleSelectPress)();
} State;

typedef struct GameState_ { // for game states (FSM)
    GameStateEnum gameStateEnum;
    void (*enterFunction)();
    void (*exitFunction)();
    void (*updateFunction)();
} GameState;

/** Collision data for 16 metatiles (1 SBB row / 1 32 tile-wide map) packed into two words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRow256x256_ {
    struct row {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
    } row;
    u32 halfSBBRow[2];
} CollisionTileRow256x256;

/** Collision data for 32 metatiles (2 SBB rows / 1 64 tile-wide map) packed into four words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRow512x512_ {
    struct rowDbl {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
        u8 t16 : 4; u8 t17 : 4; u8 t18 : 4; u8 t19 : 4; u8 t20 : 4; u8 t21 : 4; u8 t22 : 4; u8 t23 : 4;
        u8 t24 : 4; u8 t25 : 4; u8 t26 : 4; u8 t27 : 4; u8 t28 : 4; u8 t29 : 4; u8 t30 : 4; u8 t31 : 4;
    } row;
    u32 halfSBBRow[4];
} CollisionTileRow512x512;

/** Collision data for 64 metatiles (4 SBB rows / 1 128 tile-wide map) packed into eight words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRow1024x1024_ {
    struct rowQdrpl {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
        u8 t16 : 4; u8 t17 : 4; u8 t18 : 4; u8 t19 : 4; u8 t20 : 4; u8 t21 : 4; u8 t22 : 4; u8 t23 : 4;
        u8 t24 : 4; u8 t25 : 4; u8 t26 : 4; u8 t27 : 4; u8 t28 : 4; u8 t29 : 4; u8 t30 : 4; u8 t31 : 4;
        u8 t32 : 4; u8 t33 : 4; u8 t34 : 4; u8 t35 : 4; u8 t36 : 4; u8 t37 : 4; u8 t38 : 4; u8 t39 : 4;
        u8 t40 : 4; u8 t41 : 4; u8 t42 : 4; u8 t43 : 4; u8 t44 : 4; u8 t45 : 4; u8 t46 : 4; u8 t47 : 4;
        u8 t48 : 4; u8 t49 : 4; u8 t50 : 4; u8 t51 : 4; u8 t52 : 4; u8 t53 : 4; u8 t54 : 4; u8 t55 : 4;
        u8 t56 : 4; u8 t57 : 4; u8 t58 : 4; u8 t59 : 4; u8 t60 : 4; u8 t61 : 4; u8 t62 : 4; u8 t63 : 4;
    } row;
    u32 halfSBBRow[8];
} CollisionTileRow1024x1024;

typedef struct TileCollArray_ {
    u16 row[16];
} TileCollArray;

typedef union SplitWord {
    s32 WORD;
    u32 WORD_U;
    struct {
        s16 LO, HI;
    } HALF;
    struct {
        u16 LO, HI;
    } HALF_U;
    struct {
        u8 byte0, byte1, byte2, byte3;
    } BYTES;
} SWord;

typedef union SplitHWord {
    s16 HWORD;
    u16 HWORD_U;
    struct {
        s8 LO : 4;
        u16 HI : 12;
    } HALF;
    struct {
        u8 LO : 4;
        u16 HI : 12;
    } HALF_U;
    struct {
        u8 byte1, byte2;
    } BYTES;
} SHWord;

typedef struct ActionTile_ {
    u32 id; // index of metatile in collMap used as id. MUST BE FIRST
    struct data_ {
        s16 respawnTime;
        u8 tileClass; // index into fp array
        u8 action; // if tileClass == 15, or item index if tileClass == 14
    } data;
} ActionTile;

typedef struct TreeNode_ {
    struct TreeNode_* left;
    struct TreeNode_* right;
    ActionTile tile;
    s16 height;
    s16 timer;
} TreeNode;

typedef struct Viewport_ {
    s16 x, xMin, xMax,
        y, yMin, yMax;
} Viewport;

typedef enum Direction_ {
    EAST = 0,
    NORTHEAST = 0x2000,
    NORTH = 0x4000,
    NORTHWEST = 0x6000,
    WEST = 0x8000,
    SOUTHWEST = 0xA000,
    SOUTH = 0xC000,
    SOUTHEAST = 0xE000,
    STATIONARY = 0x10000
} Direction;

enum DirectionSmall_ {
    EAST_S = 0,
    NORTHEAST_S = 1,
    NORTH_S = 2,
    NORTHWEST_S = 3,
    WEST_S = 4,
    SOUTHWEST_S = 5,
    SOUTH_S = 6,
    SOUTHEAST_S = 7,
    STATIONARY_S = 8
};

enum Angle_ { // common angles in radians (cardinal+diagonal)
    ZEROPI = 0,
    QUARTERPI = 0x2000,
    HALFPI = 0x4000,
    THREEQUARTERPI = 0x6000,
    PI = 0x8000
};

typedef enum {
    NO_COLL = 0,
    REG_COLL = 1
} CollType;

typedef enum SceneEnum_ {
    Grassland = 0,
    Home = 1,
    Uglybig = 2,
    Ramp = 3
} SceneEnum;

struct SceneData {
    const SCR_ENTRY* sourceMap;
    const void* sourceCollisionMap;
    ActionTile* actionTileArray;
    SceneEnum sceneId;
    u8 mapWInMtiles;
    u8 mapHInMtiles;
};

typedef struct Scene_ {
    struct SceneData sceneData;
    TreeNode* actionTileTree;
    void* collisionMap;
    s16 screenX;
    s16 screenY;
    u8 numEnts;

    u16 tid : 9;
    u16 pb : 4;
} Scene;

const typedef struct Attack_ {
    u16 countdown; // must not be greater than 1023 (~17 seconds)
    u16 duration; // must not be greater than 1023 (~17 seconds)
    u16 cooldown;
    u8 range[MAX_ATK_RANGE]; // dmg values for each collision type (each type's index shown above)
    u8 atkClass;
    u8 anim;
    u8 id;
} Attack;

typedef struct AttackInstance_ {
    struct AttackInstance_* next;
    Attack* attack;
    s16 timer; // always initialised to countdown + duration
    s16 cooldownTimer;
    u8 firing;
    u8 toBeDeleted;
} AttackInstance;

typedef struct Position_ {
    SWord x;
    SWord y;
} Position;

typedef struct Hitbox_ {
    u8 width;
    u8 height;
    s8 leftOffset; // offset from pos.x to get left edge coord
    s8 rightOffset; // offset from pos.x to get right edge coord
    s8 topOffset; // offset from pos.y to get top edge coord
    s8 bottomOffset; // offset from pos.y to get bottom edge coord
    s8 xOffset; // whole hitbox offset on x axis
    s8 yOffset; // whole hitbox offset on y axis
} Hitbox;

typedef struct Entity_ {
    // linked list
    struct Entity_* prev; // 4 bytes
    struct Entity_* next; // 4 bytes

    // shadow OAM entries
    OBJ_ATTR* obj; // 4 bytes
    OBJ_AFFINE* obj_aff; // 4 bytes

    // important
    Position position; // 8 bytes
    Hitbox hitbox; // 8 bytes
    void (*moveSprite)(struct Entity_* ent, Position offset); // 4 bytes
    int health; // 4 bytes
    AttackInstance* attacksActive; // 4 bytes
    SWord radius; // 4 bytes. Top speed
    SWord speed; // 4 bytes. scalar value
    u32 collision; // 4 bytes
    int angleOffset; // 4 bytes
    u16 angle; // 2 bytes
    u16 angleVisual; // 2 bytes
    u16 tid; // 2 bytes
    u16 remoteControlCountdown; // 2 bytes. No. of frames before control is handed back to the player. 65535 means indefinite
    u8 affIndex; // 1 byte
    u8 ilk; // 1 byte
    u8 invincibleTime; // 1 byte
    u8 toBeDeleted; // 1 byte

    // visual
    u8 pb; // 1 byte
    u8 animationState; // 1 byte
    u8 animFrames; // 1 byte. how many frames ent has been in current animation state
    u8 numSprites; // 1 byte. how many sprites this entity has
    u8 width; // 1 byte
    u8 height; // 1 byte
    u8 spriteShape; // 1 byte, needs to be shifted left by 12 to be used in OAM
    u8 spriteSize; // 1 byte, needs to be shifted left by 12 to be used in OAM
    u8 objectMode; // 1 byte, needs to be shifted left by ATTR0_MODE_SHIFT (8) to be used in OAM
} Entity;

typedef struct Node_ {
    void* data;
    struct Node_* next;
} Node;

/** Rounds a fixed point number (SplitWord) by adding 0x8000 and masking off the fractional bits */
inline u32 sWRound(SWord num) {
    return (num.WORD + 0x8000) & 0xFFFF0000u;
}

inline u16 sHWRound(SWord num) {
    return (num.WORD + 0x8000) >> 16;
}

/** Round down to a multiple of pi (0x8000) */
inline u32 piRound(u16 angle) {
    return angle >> 15 << 15;
}

/** Round down to a multiple of pi (0x8000) */
inline u32 hPiRound(u16 angle) {
    return angle >> 14 << 14;
}

/** Returns 1 if angle is in positive X direction, -1 otherwise*/
static inline int anglePositiveX(u16 angle) {
    return !in_range(angle, 0x4000, 0xC000);
}

/** Returns 1 if angle is in positive Y direction (down), -1 otherwise*/
static inline int anglePositiveY(u16 angle) {
    return in_range(angle, 0, 0x7FFF);
}

#define DIR_COMPASS_MASK    0b011111111
#define DIAGONAL_MASK       0b011110000

Node* createStack(void* data);

Node* stackPush(Node* node, void* data);

Node* pop(Node* node);

void deleteStack(Node* node);

#endif
