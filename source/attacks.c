#include "attacks.h"

const Attack basicAtk = {
    .range = {ATK_CTR_COLL, 0, 0, 0, 0, 0, 0, 0, 0},
    .dmg = 2,
    .class = 1,
    .anim = 0,
    .countdown = 60,
    .duration = 255
};

const Attack screenAtk = {
    .range = {ATK_CTR_COLL, ATK_NW_COLL, ATK_NE_COLL, ATK_SW_COLL, ATK_SE_COLL,
        ATK_E_COLL, ATK_S_COLL, ATK_W_COLL, ATK_N_COLL},
    .dmg = 1,
    .class = 1,
    .anim = 0,
    .countdown = 120,
    .duration = 120
};
