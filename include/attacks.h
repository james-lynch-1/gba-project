#ifndef attacksh
#define attacksh

#include <tonc.h>
#include "constants.h"

// crosshair-ent attack collisions
#define ATK_NO_COLL  0
#define ATK_NW_COLL  12
#define ATK_NE_COLL  9
#define ATK_SW_COLL  6
#define ATK_SE_COLL  3
#define ATK_E_COLL   11
#define ATK_S_COLL   7
#define ATK_W_COLL   14
#define ATK_N_COLL   13
#define ATK_CTR_COLL 15

const typedef struct Attack_ {
    u8 range[MAX_ATK_RANGE]; // list of crosshair collision types that it returns true for
    u8 dmg;
    u8 class;
    u8 anim;
    u16 countdown; // must not be greater than 511, because of UI nonsense
    u16 duration; // must not be greater than 511, because of UI nonsense
} Attack;

typedef struct AttackInstance_ {
    struct AttackInstance_* next;
    Attack* attack;
    int timer; // always initialised to countdown + duration
} AttackInstance;

extern const Attack basicAtk;

extern const Attack screenAtk;

#endif
