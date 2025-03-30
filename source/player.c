#include <tonc.h>
#include "player.h"
#include "log.h"

extern Entity* entities;
extern Scene* scene;
extern int numEnts;
extern int numAttacks;
extern u32 frameCount;
extern Position crosshairPos;
extern Direction dPadDir;

void handleInput() {
    Entity* player = entities;
    union SplitWord radius = player->radius;
    union SplitWord speed = player->speed;
    u8 prevAnimState = player->animationState;
    Hitbox hb = player->hitbox;
    key_poll();

    if (player->invincibleTime) player->invincibleTime--;
    if (speed.WORD == 0) player->animationState = ANIM_IDLE;
    else player->animationState = ANIM_WALK;
    updatePlayerAnimation(player, prevAnimState);
    int direction[2] = { key_tri_horz(), key_tri_vert() };
    dPadDir = getDir(direction, dPadDir);
    if (player->remoteControlCountdown) {
        player->remoteControlCountdown--;
        speed.WORD *= 4;
        player->animFrames = 0;
    }

    crosshairPos.x.HALF.HI += key_tri_horz();
    crosshairPos.y.HALF.HI += key_tri_vert();
    player->angle -= 0x300 * key_tri_shoulder();
    speed.WORD -= 0x4000 * !key_is_down(KEY_A);
    speed.WORD = clamp(speed.WORD + (0x8000 * key_is_down(KEY_A)), 0, radius.WORD);

    // update affine stuff
    updateEntityAffine(player);

    if (key_hit(KEY_SELECT)) {
        int id = (scene->sceneData.sceneId) + 1;
        if (id >= NUM_SCENES) id = 0;
        player->position.x.WORD = 180 << 16;
        player->position.y.WORD = 160 << 16;
        loadScene(scene, id);
        return;
    }
    if (key_hit(KEY_START)) {
        switch (key_is_down(KEY_RIGHT) + key_is_down(KEY_DOWN) +
            key_is_down(KEY_LEFT) + key_is_down(KEY_UP)) {
            case 0x10: pushNewAttack(&eastAtk); break;
            case 0x80: pushNewAttack(&southAtk); break;
            case 0x20: pushNewAttack(&westAtk); break;
            case 0x40: pushNewAttack(&northAtk); break;
            case 0x90: pushNewAttack(&southeastAtk); break;
            case 0xA0: pushNewAttack(&southwestAtk); break;
            case 0x60: pushNewAttack(&northwestAtk); break;
            case 0x50: pushNewAttack(&northeastAtk); break;
            default: pushNewAttack(&crossAtk); break;
        }
    }

    bool isSpinning = checkForSpin(dPadDir);
    if (isSpinning) pushNewAttack(&basicAtk);
    crosshairPos.x.WORD = clamp(crosshairPos.x.WORD, CROSSHAIRS_X_MIN << 16, (CROSSHAIRS_X_MAX) << 16);
    crosshairPos.y.WORD = clamp(crosshairPos.y.WORD, CROSSHAIRS_Y_MIN << 16, (CROSSHAIRS_Y_MAX) << 16);

    Position nextPos = getNextPosition(player);
    player->position = nextPos;
    player->speed = speed;

    int nextId = NUM_SCENES;
    if (player->position.x.HALF.HI < 8) {
        nextId = scene->sceneData.sceneId == 0 ? NUM_SCENES - 1 : scene->sceneData.sceneId - 1;
        player->position.x.HALF.HI = sceneDataArr[nextId].mapWInMtiles * MT_WIDTH - 8;
    }
    else if (player->position.x.HALF.HI > scene->sceneData.mapWInMtiles * MT_WIDTH - 8) {
        nextId = scene->sceneData.sceneId == NUM_SCENES - 1 ? 0 : scene->sceneData.sceneId + 1;
        player->position.x.HALF.HI = 8;
    }
    if (nextId != NUM_SCENES) {
        player->position.y.HALF.HI = clamp(player->position.y.HALF.HI, hBoxTOffset(hb),
            sceneDataArr[nextId].mapHInMTiles * MT_WIDTH - hBoxBOffset(hb) - 2);
        loadScene(scene, nextId);
    }
}

Direction getDir(int direction[2], Direction dir) {
    switch ((direction[0] + 2) + 3 * (direction[1] + 2)) {
        case 4:     return NORTHWEST;               ////////////
        case 7:     return WEST;                  //     128    //
        case 10:    return SOUTHWEST;            //192         64//
        case 5:     return NORTH;               //                //
        case 11:    return SOUTH;               //256    :)      0//512
        case 6:     return NORTHEAST;           //                //
        case 9:     return EAST;                 //320        448//
        case 12:    return SOUTHEAST;             //     384    //
        default:    return dir | STATIONARY;        ////////////
    }
}

/** doesn't account for different collTypes yet */
Position getNextPosition(Entity* player) {
    Position nextPos = {
        .x = handleCollisionX(player),
        .y = handleCollisionY(player)
    };
    nextPos.y.HALF.HI = clamp(nextPos.y.HALF.HI, hBoxTOffset(player->hitbox) + 4,
        scene->sceneData.mapHInMTiles * MT_WIDTH - hBoxBOffset(player->hitbox) - 1);
    return nextPos;
}

void updateEntityAffine(Entity* player) {
    u16 off = player->angleOffset;
    obj_aff_rotscale(player->obj_aff, 256, 256, player->angle + player->angleOffset);
    mgbaLog(U16 VA off);
    obj_aff_copy(obj_aff_mem, player->obj_aff, 1);
}

void dig(Entity* player, Scene* scene) {
    MtTileArray tiles = posToMtTiles(player->position, scene);
    mgbaLog(U16 VA tiles.t0);
    mgbaLog(U16 VA tiles.t1);
    mgbaLog(U16 VA tiles.t2);
    mgbaLog(U16 VA tiles.t3);
}

void updateAttacks() {
    // decrement attack timers and delete completed attacks
    AttackInstance* atk = entities->attacksActive;
    // if the first one has timer == 0
    while (atk != NULL && atk->timer == 0) {
        entities->attacksActive = entities->attacksActive->next;
        free(atk);
        numAttacks--;
        atk = entities->attacksActive;
    }
    // now assuming the first one has non-zero timer
    int atkIndex = 0;
    while (atk != NULL) {
        if (atk->next && atk->next->timer == 0) { // checking/deleting the next one cos no prev pointer
            AttackInstance* newNext = atk->next->next;
            deleteNextAtkInstance(atk);
            numAttacks--;
            atk->next = newNext;
        }
        updateQuadCountdownUI(atk->timer, atk->attack->countdown, atk->attack->duration, atkIndex);
        atkIndex++;
        atk->timer--;
        atk = atk->next;
    }
}

// checks for series of inputs resulting in a spin
bool checkForSpin(Direction dir) {
    static int anticlockwise;
    static int waitFrames = 0;
    static int numOfSpinInputs = 0;
    static Direction initDir = STATIONARY;
    bool doSpin = false;
    Direction cardinalDir = dir >> 14 << 14;
    if (numOfSpinInputs == 8 || waitFrames == SPIN_WAIT_FRAMES) {
        doSpin = numOfSpinInputs == 8;
        anticlockwise = -1;
        waitFrames = 0;
        numOfSpinInputs = 0;
        initDir = STATIONARY;
        return doSpin;
    }
    if (numOfSpinInputs == 0) {
        initDir = cardinalDir;
        numOfSpinInputs++;
        return false;
    }
    if (numOfSpinInputs == 1 && (cardinalDir == ((initDir + 0x4000) & 0xFFFF))) anticlockwise = 1;
    else if (numOfSpinInputs == 1 && (cardinalDir == ((initDir - 0x4000) & 0xFFFF))) anticlockwise = -1;
    if (cardinalDir == ((initDir + anticlockwise * numOfSpinInputs * 0x4000) & 0xFFFF)) {
        waitFrames = 0;
        numOfSpinInputs++;
        return false;
    }
    waitFrames++;
    return false;
}

void updatePlayerAnimation(Entity* player, u8 prevAnimState) {
    if (player->invincibleTime) { // invincibility flashing
        if (frameCount & 1) player->obj->attr0 ^= ATTR0_AFF_DBL; // flips from affine flag (01) to hidden flag (10)
    }
    else {
        player->obj->attr0 &= !ATTR0_AFF_DBL;
        player->obj->attr0 |= ATTR0_AFF;
    }
    updateAnimation(player, prevAnimState);
}

int getNextDiffX(int x, union SplitWord speed, u32 angle) {
    return ((((s64)(lu_cos(angle)) << 4) * speed.WORD) >> 16);
}

int getNextDiffY(int y, union SplitWord speed, u32 angle) {
    return ((((s64)(-lu_sin(angle)) << 4) * speed.WORD) >> 16);
}

u16 getAngle(Direction dir, u32 angle) {
    switch (dir) {
        case EAST: return 0;
        case NORTHEAST: return 0x2000;
        case NORTH: return 0x4000;
        case NORTHWEST: return 0x6000;
        case WEST: return 0x8000;
        case SOUTHWEST: return 0xA000;
        case SOUTH: return 0xC000;
        case SOUTHEAST: return 0xE000;
        default: return angle;
    }
}


/** Finds closest possible position to the wall the ent is colliding with on the x axis. */
union SplitWord handleCollisionX(Entity* ent) {
    u32 angle = ent->angle;
    union SplitWord speed = ent->speed, speedTest = { 0 };
    Direction xDir = (EAST + !anglePositiveX(angle) * 0x8000) & 0xFFFF;
    Position pos = ent->position;
    Position posArr[2] = {pos, pos}; // nextPos, nextNextPos
    u32 coll = 0;
    do {
        posArr[0] = posArr[1];
        speedTest.WORD = clamp(speedTest.WORD + 0x10000, 0, speed.WORD + 1);
        posArr[1].x.WORD = pos.x.WORD + getNextDiffX(pos.x.WORD, speedTest, angle);
        coll = getEdgeCollision(posArr[1], ent, xDir, scene);
    } while (coll == 0 && speedTest.WORD < speed.WORD);
    return posArr[coll == 0].x;
}

/** Finds closest possible position to the wall the ent is colliding with on the y axis. */
union SplitWord handleCollisionY(Entity* ent) {
    u32 angle = ent->angle;
    union SplitWord speed = ent->speed, speedTest = { 0 };
    Direction yDir = (NORTH + !anglePositiveY(angle) * 0x8000) & 0xFFFF;
    Position pos = ent->position;
    Position posArr[2] = {pos, pos}; // nextPos, nextNextPos
    u32 coll = 0;
    do {
        posArr[0] = posArr[1];
        speedTest.WORD = clamp(speedTest.WORD + 0x10000, 0, speed.WORD + 1);
        posArr[1].y.WORD = pos.y.WORD + getNextDiffY(pos.y.WORD, speedTest, angle);
        coll = getEdgeCollision(posArr[1], ent, yDir, scene);
    } while (coll == 0 && speedTest.WORD < speed.WORD);
    return posArr[coll == 0].y;
}
