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
    U16HEX,
    U32,
    U32HEX,
    SPLITWORD,
    USPLITWORD
} Type;

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
    bool toBeDeleted; // 4 bytes

    // shadow OAM entries
    OBJ_ATTR* obj; // 4 bytes
    OBJ_AFFINE* obj_aff; // 4 bytes

    // important
    void (*moveSprite)(struct Entity_* ent, Position offset); // 4 bytes
    int health; // 4 bytes
    Position position; // 8 bytes
    Hitbox hitbox; // 8 bytes
    AttackInstance* attacksActive; // 4 bytes
    SWord radius; // 4 bytes. Top speed
    SWord speed; // 4 bytes. scalar value
    u16 angleOffset; // 2 bytes
    u16 angle; // 2 bytes
    u16 tid; // 2 bytes
    u16 remoteControlCountdown; // 2 bytes. No. of frames before control is handed back to the player. 65535 means indefinite
    u8 affIndex; // 1 byte
    u8 ilk; // 1 byte
    u8 invincibleTime; // 1 byte

    // visual
    u8 pb; // 1 byte
    u8 animationState; // 1 byte
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

void enqueue(Node** head, int val);

int dequeue(Node** head);

#define DIR_COMPASS_MASK    0b011111111
#define DIAGONAL_MASK       0b011110000

#endif
