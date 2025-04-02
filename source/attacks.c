#include "attacks.h"

// Range array: E, S, W, N, SE, SW, NW, NE, CTR

const Attack basicAtk = {
    .range = {0, 0, 0, 0, 0, 0, 0, 0, 2},
    .class = 1,
    .anim = 0,
    .countdown = 20,
    .duration = 120
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
    .duration = 512
};
