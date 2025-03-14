#ifndef typeh
#define typeh

#include <tonc.h>
#include <stdlib.h>

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

typedef struct Node_ {
    int val;
    struct Node_* next;
} Node;

// typedef enum Direction_
// {
//     EAST =          0b000000001,
//     SOUTH =         0b000000010,
//     WEST =          0b000000100,
//     NORTH =         0b000001000,
//     SOUTHEAST =     0b000010000,
//     SOUTHWEST =     0b000100000,
//     NORTHEAST =     0b001000000,
//     NORTHWEST =     0b010000000,
//     STATIONARY =    0b100000000
// } Direction;

typedef enum {
    NO_COLL = 0,
    REG_COLL = 1
} CollType;

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

typedef struct Position_ {
    union SplitWord x;
    union SplitWord y;
} Position;

/** Rounds a fixed point number (SplitWord) by adding 0x8000 and shifting a bunch */
inline u32 sWRound(union SplitWord num) {
    return (num.WORD + 0x8000) >> 16 << 16;
}

inline u16 sHWRound(union SplitWord num) {
    return (num.WORD + 0x8000) >> 16;
}

void enqueue(Node** head, int val);

int dequeue(Node** head);

#define DIR_COMPASS_MASK    0b011111111
#define DIAGONAL_MASK       0b011110000

#endif
