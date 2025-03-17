#include "attacks.h"

// crosshair-ent collision array indices
// #define ATK_E_COLL   0
// #define ATK_S_COLL   1
// #define ATK_W_COLL   2
// #define ATK_N_COLL   3
// #define ATK_SE_COLL  4
// #define ATK_SW_COLL  5
// #define ATK_NW_COLL  6
// #define ATK_NE_COLL  7
// #define ATK_CTR_COLL 8

const Attack basicAtk = {
    .range = {0, 0, 0, 0, 0, 0, 0, 0, 2},
    .class = 1,
    .anim = 0,
    .countdown = 60,
    .duration = 255
};

const Attack screenAtk = {
    .range = {2, 2, 2, 2, 2, 2, 2, 2, 2},
    .class = 1,
    .anim = 0,
    .countdown = 120,
    .duration = 240
};

const Attack eastAtk = {
    .range = {2, 0, 0, 0, 0, 0, 0, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack southAtk = {
    .range = {0, 2, 0, 0, 0, 0, 0, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack westAtk = {
    .range = {0, 0, 2, 0, 0, 0, 0, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack northAtk = {
    .range = {0, 0, 0, 2, 0, 0, 0, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack southeastAtk = {
    .range = {0, 0, 0, 0, 2, 0, 0, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack southwestAtk = {
    .range = {0, 0, 0, 0, 0, 2, 0, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack northwestAtk = {
    .range = {0, 0, 0, 0, 0, 0, 2, 0, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack northeastAtk = {
    .range = {0, 0, 0, 0, 0, 0, 0, 2, 0},
    .class = 1,
    .anim = 0,
    .countdown = 30,
    .duration = 120
};

const Attack crossAtk = {
    .range = {2, 2, 2, 2, 0, 0, 0, 0, 4},
    .class = 1,
    .anim = 0,
    .countdown = 0,
    .duration = 255
};
