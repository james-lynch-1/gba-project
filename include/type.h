#ifndef typeh
#define typeh

#include <tonc.h>
#include <stdlib.h>
#include "constants.h"

typedef enum {
    CHAR,
    DIRECTION,
    PTR,
    INT,
    INTHEX,
    S16,
    S32,
    U16,
    U32,
    U32HEX,
    SPLITWORD,
    USPLITWORD
} Type;

typedef struct Viewport_ {
    s16 x, xMin, xMax,
        y, yMin, yMax;
} Viewport;

typedef enum Direction_ {
    EAST = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3,
    SOUTHEAST = 4,
    SOUTHWEST = 5,
    NORTHWEST = 6,
    NORTHEAST = 7,
    STATIONARY = 8,
    DIAGONAL = 4
} Direction;

typedef enum {
    NO_COLL = 0,
    REG_COLL = 1
} CollType;

typedef enum SceneEnum_ {
    Grassland = 0,
    Home = 1,
    Uglybig = 2
} SceneEnum;

struct SceneData {
    SceneEnum sceneId;
    const SCR_ENTRY* sourceMap;
    void* collisionMap;
    u8 mapWInMtiles;
    u8 mapHInMTiles;
};

typedef struct Scene_ {
    struct SceneData sceneData;
    s16 screenX;
    s16 screenY;
    u8 numEnts;
    u16 tid : 9;
    u16 pb : 4;
} Scene;

const typedef struct Attack_ {
    u8 range[MAX_ATK_RANGE]; // dmg values for each collision type (each type's index shown above)
    u8 class;
    u8 anim;
    u16 countdown; // must not be greater than 255, because of UI nonsense
    u16 duration; // must not be greater than 255, because of UI nonsense
} Attack;

typedef struct AttackInstance_ {
    struct AttackInstance_* next;
    Attack* attack;
    int timer; // always initialised to countdown + duration
} AttackInstance;

union SplitWord {
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
};

typedef struct Position_ {
    union SplitWord x;
    union SplitWord y;
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
    bool toBeDeleted; // 4 bytes

    // shadow OAM entries
    OBJ_ATTR* obj; // 4 bytes
    OBJ_AFFINE* obj_aff; // 4 bytes

    // important
    void (*moveSprite)(struct Entity_* ent, Position offset); // 4 bytes
    int health; // 4 bytes
    Position position; // 8 bytes
    Hitbox hitbox; // 8 bytes
    union SplitWord speed; // 4 bytes
    union SplitWord rotation; // 4 bytes
    Direction dir; // 4 bytes
    u16 tid; // 2 bytes
    u16 remoteControlCountdown; // 2 bytes. No. of frames before control is handed back to the player. 65535 means indefinite
    AttackInstance* attacksActive; // 4 bytes
    u8 affIndex; // 1 byte
    u8 ilk; // 1 byte
    u8 invincibleTime; // 1 byte

    // visual
    u8 pb; // 1 byte
    u8 animationState; // 1 byte
    u8 facing; // 1 byte
    u8 facingLocked; // 1 byte
    u8 animFrames; // 1 byte. how many frames ent has been in current animation state
    u8 width; // 1 byte
    u8 height; // 1 byte
    u8 spriteShape; // 1 byte, needs to be shifted left by 12 to be used in OAM
    u8 spriteSize; // 1 byte, needs to be shifted left by 12 to be used in OAM
    u8 spriteType; // 1 byte, needs to be shifted left by ATTR0_MODE_SHIFT (8) to be used in OAM
} Entity;

typedef struct Node_ {
    int val;
    struct Node_* next;
} Node;

union SplitHalfWord {
    s16 HWORD;
    u16 HWORD_U;
    struct {
        s8 LO, HI;
    } HALF;
    struct {
        u8 LO, HI;
    } HALF_U;
};

/** Rounds a fixed point number (SplitWord) by adding 0x8000 and masking off the fractional bits */
inline u32 sWRound(union SplitWord num) {
    return (num.WORD + 0x8000) & 0xFFFF0000u;
}

inline u16 sHWRound(union SplitWord num) {
    return (num.WORD + 0x8000) >> 16;
}

void enqueue(Node** head, int val);

int dequeue(Node** head);

#define DIR_COMPASS_MASK    0b011111111
#define DIAGONAL_MASK       0b011110000

#endif
