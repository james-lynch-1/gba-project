#include "player.h"
#include "log.h"

void handleInput() {
    Entity* player = entities;
    SWord radius = player->radius;
    SWord speed = player->speed;
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

    if (dPadDir != STATIONARY) {
        crosshairPos.x.WORD += getNextDiffX(crosshairPos.x.WORD,
            (SWord)(CROSSHAIRS_SPEED >> (key_is_down(KEY_L) != 0)), dPadDir);
        crosshairPos.y.WORD += getNextDiffY(crosshairPos.y.WORD,
            (SWord)(CROSSHAIRS_SPEED >> (key_is_down(KEY_L) != 0)), dPadDir);
    }
    player->angle = ArcTan2((crosshairPos.x.HALF.HI + scene->screenX) - player->position.x.HALF.HI,
        player->position.y.HALF.HI - (crosshairPos.y.HALF.HI + scene->screenY));
    speed.WORD = decaySpeed(speed, radius);

    // update affine stuff
    updateEntityAffine(player);

    if (key_hit(KEY_SELECT)) {
        int id = (scene->sceneData.sceneId) + 1;
        if (id >= NUM_SCENES) id = 0;
        player->position.x.WORD = 180 << 16;
        player->position.y.WORD = 160 << 16;
        unloadScene(scene);
        loadScene(scene, id);
        return;
    }
    if (key_hit(KEY_START)) {
        // switch (key_is_down(KEY_RIGHT) + key_is_down(KEY_DOWN) +
        //     key_is_down(KEY_LEFT) + key_is_down(KEY_UP)) {
        //     case 0x10: pushNewAttack(&eastAtk); break;
        //     case 0x80: pushNewAttack(&southAtk); break;
        //     case 0x20: pushNewAttack(&westAtk); break;
        //     case 0x40: pushNewAttack(&northAtk); break;
        //     case 0x90: pushNewAttack(&southeastAtk); break;
        //     case 0xA0: pushNewAttack(&southwestAtk); break;
        //     case 0x60: pushNewAttack(&northwestAtk); break;
        //     case 0x50: pushNewAttack(&northeastAtk); break;
        //     default: pushNewAttack(&crossAtk); break;
        // }

        // spawnFella(screenToWorldPos(crosshairPos));

        switchGameState(PAUSE);
    }

    bool isSpinning = checkForSpin(dPadDir);
    if (isSpinning) pushNewAttack(&crossAtk);
    crosshairPos.x.WORD = clamp(crosshairPos.x.WORD, CROSSHAIRS_X_MIN << 16, (CROSSHAIRS_X_MAX) << 16);
    crosshairPos.y.WORD = clamp(crosshairPos.y.WORD, CROSSHAIRS_Y_MIN << 16, (CROSSHAIRS_Y_MAX) << 16);

    player->angleOffset = 0;
    // int cornerMaskOffsets[4] = { 0, 8, 12, 20 };
    // int i = 0;
    // while (player->angleOffset == 0 && i < 4)
    //     player->angleOffset = getAngleOffset(player->angle, (player->collision >> cornerMaskOffsets[i++]) & 0xF);

    player->collision = 0;
    Position nextPos = getNextPosition(player);
    player->position = nextPos;
    player->speed = speed;

    int nextId = NUM_SCENES;
    if (player->position.x.HALF.HI < 16) {
        nextId = scene->sceneData.sceneId == 0 ? NUM_SCENES - 1 : scene->sceneData.sceneId - 1;
        player->position.x.HALF.HI = sceneDataArr[nextId].mapWInMtiles * MT_WIDTH - 16;
    }
    else if (player->position.x.HALF.HI > scene->sceneData.mapWInMtiles * MT_WIDTH - 16) {
        nextId = scene->sceneData.sceneId == NUM_SCENES - 1 ? 0 : scene->sceneData.sceneId + 1;
        player->position.x.HALF.HI = 16;
    }
    if (nextId != NUM_SCENES) {
        player->position.y.HALF.HI = clamp(player->position.y.HALF.HI, hBoxTOffset(hb),
            sceneDataArr[nextId].mapHInMtiles * MT_WIDTH - hBoxBOffset(hb) - 2);
        unloadScene(scene);
        loadScene(scene, nextId);
    }
}

Direction getDir(int direction[2], Direction dir) {
    switch ((direction[0] + 2) + 3 * (direction[1] + 2)) {
        case 9:     return EAST;                    ////////////
        case 6:     return NORTHEAST;             //   0x4000   //
        case 5:     return NORTH;                //0x6000  0x2000//
        case 4:     return NORTHWEST;           //                //
        case 7:     return WEST;                //0x8000 :)      0//(0x10000)
        case 10:    return SOUTHWEST;           //                //
        case 11:    return SOUTH;                //0xA000  0xE000//
        case 12:    return SOUTHEAST;             //   0xC000   //
        default:    return STATIONARY;              ////////////
    }
}

/** doesn't account for different collTypes yet */
Position getNextPosition(Entity* player) {
    Position nextPos = {
        .x = handleCollisionX(player),
        .y = handleCollisionY(player)
    };
    player->angleOffset = checkCollForAngleOffset(player->collision, player->angle);
    if (player->angleOffset) {
        nextPos.x = handleCollisionX(player);
        nextPos.y = handleCollisionY(player);
    }
    nextPos.y.HALF.HI = clamp(nextPos.y.HALF.HI, hBoxTOffset(player->hitbox) + 4,
        scene->sceneData.mapHInMtiles * MT_WIDTH - hBoxBOffset(player->hitbox) - 4);
    return nextPos;
}

void updateEntityAffine(Entity* player) {
    obj_aff_rotscale(player->obj_aff, 256, 256, player->angle + player->angleVisual);
    obj_aff_copy(obj_aff_mem, player->obj_aff, 1);
}

void dig(Entity* player, Scene* scene) {
    MtTileArray tiles = posToMtTileArray(player->position, scene);
    log(U16, tiles.t0);
    log(U16, tiles.t1);
    log(U16, tiles.t2);
    log(U16, tiles.t3);
}

void updateAttacks() {
    AttackInstance* atkInst = entities->attacksActive;
    atkInst->firing = KEY_DOWN_NOW(KEY_R) != 0;
    int atkIndex = 0;
    while (atkInst != NULL) {
        if (atkInst->next && atkInst->next->toBeDeleted) { // checking/deleting the next one cos no prev pointer
            AttackInstance* newNext = atkInst->next->next;
            deleteNextAtkInstance(atkInst);
            numAttacks--;
            atkInst->next = newNext;
        }
        updateUiFns[atkInst->attack->atkClass](atkInst, atkIndex);
        atkIndex++;
        atkUpdateFns[atkInst->attack->atkClass](atkInst);
        atkInst = atkInst->next;
    }
    if (entities->attacksActive) entities->attacksActive->toBeDeleted = 0; // can't delete the first attack
}

// checks for series of inputs resulting in a spin
bool checkForSpin(Direction dir) {
    static int difference = 0xC000;
    static int waitFrames = 0;
    static int numSpinputs = 0;
    static Direction prevDir;
    Direction cardinalDir = dir & 0xC000;
    switch (numSpinputs) {
        case NUM_SPINPUTS:
            setSpin(&prevDir, cardinalDir, &waitFrames, 0, &numSpinputs, 0);
            return true;
        case 0:
            prevDir = cardinalDir;
            numSpinputs = 1;
            return false;
        case 1:
            if (dir != STATIONARY) {
                difference = 0xC000;
                if (((cardinalDir - prevDir) & 0xFFFF) == 0x4000)
                    difference = 0x4000;
            }
        default:
            break;
    }
    if (waitFrames == SPIN_WAIT_FRAMES) {
        setSpin(&prevDir, cardinalDir, &waitFrames, 0, &numSpinputs, 0);
        return false;
    }
    if (((prevDir + difference) & 0xFFFF) == (cardinalDir & 0xFFFF)) { // correct dir in sequence
        setSpin(&prevDir, cardinalDir, &waitFrames, 0, &numSpinputs, ++numSpinputs);
        return false;
    }
    if ((((prevDir + difference) & 0xFFFF) == (-cardinalDir & 0xFFFF)) || // handle incorrect dir
        ((cardinalDir - prevDir) & 0xFFFF) == 0x8000) {
        setSpin(&prevDir, cardinalDir, &waitFrames, 0, &numSpinputs, 1);
        return false;
    }
    waitFrames++; // dir has not changed
    return false;
}

void setSpin(Direction* prevDir, Direction newDir, int* waitFrames, int newWF, int* numSpinputs, int newNS) {
    *prevDir = newDir;
    *waitFrames = newWF;
    *numSpinputs = newNS;
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

int getNextDiffX(int x, SWord speed, u32 angle) {
    return ((((s64)(lu_cos(angle)) << 4) * speed.WORD) >> 16);
}

int getNextDiffY(int y, SWord speed, u32 angle) {
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
SWord handleCollisionX(Entity* ent) {
    u32 angle = ent->angle + ent->angleOffset;
    SWord speed = ent->speed, speedTest = { 0 };
    Direction xDir = (EAST + !anglePositiveX(angle) * 0x8000) & 0xFFFF;
    Position pos = ent->position, posArr[2] = { pos, pos }; // nextPos, nextNextPos
    u32 coll = 0;
    do {
        posArr[0] = posArr[1];
        speedTest.WORD = clamp(speedTest.WORD + 0x10000, 0, speed.WORD + 1);
        posArr[1].x.WORD = pos.x.WORD + getNextDiffX(pos.x.WORD, speedTest, angle);
        coll = getEdgeCollision(posArr[1], ent->hitbox, xDir, scene);
        if (speedTest.HALF.HI == 1) ent->collision |= coll;
    } while (coll == 0 && speedTest.WORD < speed.WORD);
    return posArr[coll == 0].x;
}

/** Finds closest possible position to the wall the ent is colliding with on the y axis. */
SWord handleCollisionY(Entity* ent) {
    u32 angle = ent->angle + ent->angleOffset;
    SWord speed = ent->speed, speedTest = { 0 };
    Direction yDir = (NORTH + !anglePositiveY(angle) * 0x8000) & 0xFFFF;
    Position pos = ent->position, posArr[2] = { pos, pos }; // nextPos, nextNextPos
    u32 coll = 0;
    do {
        posArr[0] = posArr[1];
        speedTest.WORD = clamp(speedTest.WORD + 0x10000, 0, speed.WORD + 1);
        posArr[1].y.WORD = pos.y.WORD + getNextDiffY(pos.y.WORD, speedTest, angle);
        coll = getEdgeCollision(posArr[1], ent->hitbox, yDir, scene);
        if (speedTest.HALF.HI == 1) ent->collision |= coll;
    } while (coll == 0 && speedTest.WORD < speed.WORD);
    return posArr[coll == 0].y;
}

int checkCollForAngleOffset(u32 coll, u16 angle) {
    int cornerMaskOffsets[4] = { 0, 8, 12, 20 }, angleOffset = 0, i = 0;
    while (angleOffset == 0 && i < 4)
        angleOffset = getAngleOffset(angle, (coll >> cornerMaskOffsets[i++]) & 0xF);
    return angleOffset;
}

inline int decaySpeed(SWord speed, SWord radius) {
    speed.WORD -= PLAYER_DECAY_RATE * !key_is_down(KEY_A);
    return clamp(speed.WORD + (0x8000 * key_is_down(KEY_A)), 0, radius.WORD);
}
