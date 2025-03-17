#ifndef attacksh
#define attacksh

#include <tonc.h>
#include "constants.h"

// crosshair-ent collision array indices
#define ATK_E_COLL      0
#define ATK_S_COLL      1
#define ATK_W_COLL      2
#define ATK_N_COLL      3
#define ATK_SE_COLL     4
#define ATK_SW_COLL     5
#define ATK_NW_COLL     6
#define ATK_NE_COLL     7
#define ATK_CTR_COLL    8
#define MAX_ATK_RANGE   9 // no. of elements in array (cardinals + quadrants + centre)

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

extern const Attack basicAtk;
extern const Attack screenAtk;
extern const Attack eastAtk;
extern const Attack southAtk;
extern const Attack westAtk;
extern const Attack northAtk;
extern const Attack southeastAtk;
extern const Attack southwestAtk;
extern const Attack northwestAtk;
extern const Attack northeastAtk;
extern const Attack crossAtk;

#endif
