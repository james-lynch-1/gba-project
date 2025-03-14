#include "scroll.h"

extern Entity* entities;
extern Scene* scene;

void handleScroll() {
    Entity* player = entities;
    moveScreenOnMap(player, scene);
    Position screenPos = {.x.HALF.HI = scene->screenX, .y.HALF.HI = scene->screenY};
    movePlayerSpriteOnScreen(player, screenPos);
}

void moveScreenOnMap(Entity* ent, Scene* scene) {
    scene->screenX = ent->position.x.HALF.HI - (SCREEN_WIDTH / 2);
    scene->screenY = ent->position.y.HALF.HI - (SCREEN_HEIGHT / 2);

    if (ent->position.x.HALF.HI < SCREEN_WIDTH / 2)
        scene->screenX = 0;
    if (ent->position.y.HALF.HI < SCREEN_HEIGHT / 2)
        scene->screenY = 0;
    if (ent->position.x.HALF.HI > (scene->mapWidthInMetatiles * 16) - SCREEN_WIDTH / 2)
        scene->screenX = (scene->mapWidthInMetatiles * 16) - SCREEN_WIDTH;
    if (ent->position.y.HALF.HI > (scene->mapHeightInMetatiles * 16) - SCREEN_HEIGHT / 2)
        scene->screenY = (scene->mapHeightInMetatiles * 16) - SCREEN_HEIGHT;

    REG_BG0HOFS = scene->screenX;
    REG_BG0VOFS = scene->screenY;
}

void movePlayerSpriteOnScreen(Entity* player, Position screenPos) {
    obj_set_pos(player->obj, player->position.x.HALF.HI - screenPos.x.HALF.HI - (PLAYER_SPR_WIDTH / 2),
        player->position.y.HALF.HI - screenPos.y.HALF.HI - (PLAYER_SPR_HEIGHT / 2));
    obj_set_attr(player->obj, player->obj->attr0, player->obj->attr1, player->obj->attr2 | ATTR2_PRIO(3));
}

void moveSpriteOnScreen(Entity* ent, Position offset)
{
    obj_set_pos(ent->obj, ent->position.x.HALF.HI - scene->screenX - (ent->width / 2) + offset.x.HALF.HI,
    ent->position.y.HALF.HI - scene->screenY - (ent->height / 2) + offset.y.HALF.HI);
}

bool checkIfOnScreen(Entity* ent) {
    return ((ent->position.x.HALF.HI + ent->width / 2 > scene->screenX && ent->position.x.HALF.HI - ent->width / 2 < (scene->screenX + SCREEN_WIDTH)) &&
        (ent->position.y.HALF.HI + ent->height / 2 > scene->screenY && ent->position.y.HALF.HI - ent->height / 2 < (scene->screenY + SCREEN_HEIGHT)));
}
