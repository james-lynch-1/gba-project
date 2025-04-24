#include "scene.h"

void handleScroll() {
    Entity* player = entities;
    moveViewportOnMap(player, scene);
    updateBGTiles(scene);
    Position screenPos = { .x.HALF.HI = scene->screenX, .y.HALF.HI = scene->screenY };
    movePlayerSpriteOnScreen(player, screenPos);
}

void moveViewportOnMap(Entity* ent, Scene* scene) {
    vp.x = ent->position.x.HALF.HI - (SCR_W / 2);
    vp.x = clamp(vp.x, vp.xMin, vp.xMax);
    vp.y = ent->position.y.HALF.HI - (SCR_H / 2);
    vp.y = clamp(vp.y, vp.yMin, vp.yMax);
}

void movePlayerSpriteOnScreen(Entity* player, Position screenPos) {
    obj_set_pos(player->obj, player->position.x.HALF.HI - screenPos.x.HALF.HI - (PLAYER_SPR_WIDTH / 2),
        player->position.y.HALF.HI - screenPos.y.HALF.HI - (PLAYER_SPR_HEIGHT / 2));
    obj_set_attr(player->obj, player->obj->attr0, player->obj->attr1, player->obj->attr2 | ATTR2_PRIO(3));
}

void moveSpriteOnScreen(Entity* ent, Position offset) {
    obj_set_pos(ent->obj, ent->position.x.HALF.HI - scene->screenX - (ent->width / 2) + offset.x.HALF.HI,
        ent->position.y.HALF.HI - scene->screenY - (ent->height / 2) + offset.y.HALF.HI);
}

bool checkIfOnScreen(Entity* ent) {
    return ((ent->position.x.HALF.HI + ent->width / 2 > scene->screenX && ent->position.x.HALF.HI - ent->width / 2 < (scene->screenX + SCR_W)) &&
        (ent->position.y.HALF.HI + ent->height / 2 > scene->screenY && ent->position.y.HALF.HI - ent->height / 2 < (scene->screenY + SCR_H)));
}

// adapted from bigmap demo in libtonc-examples
void updateBGTiles(Scene* scene) {
    int oldTileX = (scene->screenX) / 8;
    int oldTileY = (scene->screenY) / 8;
    int tileX = vp.x / 8;
    int tileY = vp.y / 8;

    if (tileX < oldTileX) // scroll left
        copyTileCol(scene, tileX, tileY);
    else if (tileX > oldTileX) // scroll right
        copyTileCol(scene, tileX + 30, tileY);
    
    if (tileY < oldTileY) // scroll up
        copyTileRow(scene, tileX, tileY);
    else if (tileY > oldTileY) // scroll down
        copyTileRow(scene, tileX, tileY + 30);
    scene->screenX = vp.x;
    scene->screenY = vp.y;

    REG_BG0HOFS = scene->screenX;
    REG_BG0VOFS = scene->screenY;
}

bool mTileIsWithinViewport(Position pos, Viewport vp) {
    return ((pos.x.HALF.HI > vp.x - 16) && (pos.x.HALF.HI < vp.x + SCREEN_WIDTH) &&
            (pos.y.HALF.HI > vp.y - 16) && (pos.y.HALF.HI < vp.y + SCREEN_HEIGHT));
}
