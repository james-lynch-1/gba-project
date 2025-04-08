#include "hitbox.h"

Hitbox playerHitbox = {
    .width = 15, .height = 15, .leftOffset = -7, .rightOffset = 7,
    .topOffset = -7, .bottomOffset = 7, .xOffset = 0, .yOffset = 0
};

Hitbox fellaHitbox = {
    .width = 8, .height = 8, .leftOffset = -4, .rightOffset = 3,
    .topOffset = -4, .bottomOffset = 3, .xOffset = 0, .yOffset = 0
};
