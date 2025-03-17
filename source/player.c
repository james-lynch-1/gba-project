#include <tonc.h>
#include "player.h"
#include "entity.h"
#include "constants.h"
#include "log.h"

extern Entity* entities;
extern Scene* scene;
extern Direction spinArray[8];
extern int numEnts;
extern int numAttacks;
extern u32 frameCount;
extern Position crosshairPos;

void handleInput() {
    Entity* player = entities;
    key_poll();
    union SplitWord speed = player->speed;
    union SplitWord normalisedSpeed = speed;
    if ((player->dir & DIAGONAL) != 0) {
        normalisedSpeed.WORD = fxmul64(speed.WORD, sin_lut[0x40] << 4) >> 8;
    }
    Hitbox hb = player->hitbox;

    if (player->invincibleTime) player->invincibleTime--;
    u8 prevAnimState = player->animationState;
    if ((player->dir & STATIONARY) != 0) player->animationState = ANIM_IDLE;
    else player->animationState = ANIM_WALK;
    updatePlayerAnimation(player, prevAnimState);
    int direction[2] = { key_tri_horz(), key_tri_vert() };
    if (player->remoteControlCountdown) {
        player->remoteControlCountdown--;
        normalisedSpeed.WORD *= 4;
        player->animFrames = 0;
    }
    else {
        player->dir = getDir(direction, player->dir);
        player->facingLocked = 0;
    }

    if (!player->facingLocked) player->facing = getFacing(player);

    if (key_is_down(KEY_L)) {
        // player->rotation.WORD += 0x200;
        crosshairPos.x.WORD -= 0x10000;
    }
    if (key_is_down(KEY_R)) {
        // player->rotation.WORD -= 0x200;
        crosshairPos.x.WORD += 0x10000;
    }
    // if (key_hit(KEY_R)) {
    //     player->prev->toBeDeleted = true;
    // }
    if (key_hit(KEY_SELECT)) {
        int id = (scene->sceneId) + 1;
        if (id >= NUM_SCENES) id = 0;
        loadScene(scene, id);
        player->position.x.WORD = 72 << 16;
        player->position.y.WORD = 72 << 16;
        return;
    }
    if (key_is_down(KEY_A)) {
        // dig(player, scene);
        crosshairPos.y.WORD += 0x10000;
    }
    if (key_is_down(KEY_B)) {
        crosshairPos.y.WORD -= 0x10000;
    }
    if (key_hit(KEY_START)) {
        // speed.HALF.HI = 1;
        // speed.HALF.LO = 0;
        // player->rotation.WORD = 0;
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

    bool isSpinning = checkForSpin(player->dir);
    if (isSpinning) pushNewAttack(&basicAtk);

    if (crosshairPos.x.HALF.HI < CROSSHAIRS_X_MIN)
        crosshairPos.x.WORD = MT_WIDTH << 16;
    if (crosshairPos.x.HALF.HI > CROSSHAIRS_X_MAX)
        crosshairPos.x.WORD = (CROSSHAIRS_X_MAX) << 16;
    if (crosshairPos.y.HALF.HI < CROSSHAIRS_Y_MIN)
        crosshairPos.y.WORD = CROSSHAIRS_Y_MIN << 16;
    if (crosshairPos.y.HALF.HI > CROSSHAIRS_Y_MAX)
        crosshairPos.y.WORD = (CROSSHAIRS_Y_MAX) << 16;
    if (speed.WORD > PLAYER_MAX_SPEED) speed.WORD = PLAYER_MAX_SPEED;
    if (speed.WORD < 0) speed.WORD = 0;

    int xDirSign = 0, yDirSign = 0;
    switch (player->dir) {
        case NORTH: xDirSign = 0; yDirSign = -1; break;
        case SOUTH: xDirSign = 0; yDirSign = 1; break;
        case EAST: xDirSign = 1; yDirSign = 0; break;
        case WEST: xDirSign = -1; yDirSign = 0; break;
        case SOUTHEAST: xDirSign = 1; yDirSign = 1; break;
        case SOUTHWEST: xDirSign = -1; yDirSign = 1; break;
        case NORTHWEST: xDirSign = -1; yDirSign = -1; break;
        case NORTHEAST: xDirSign = 1; yDirSign = -1; break;
        default: break;
    }
    Position nextPos = { {player->position.x.WORD + normalisedSpeed.WORD * xDirSign},
                         {player->position.y.WORD + normalisedSpeed.WORD * yDirSign} };

    u32 collision = getTileCollision(nextPos, player, scene);

    nextPos = handleCollision(player, normalisedSpeed, nextPos, collision, scene);

    if (nextPos.x.HALF.HI < 8) {
        loadPreviousScene(scene);
        player->position.x.WORD = ((scene->mapWidthInMetatiles * MT_WIDTH) - 8) << 16;
        if (player->position.y.HALF.HI > scene->mapHeightInMetatiles * MT_WIDTH - hBoxBOffset(hb) - 2)
            player->position.y.WORD = 245 << 16;
        return;
    }
    if (nextPos.x.HALF.HI > scene->mapWidthInMetatiles * MT_WIDTH - 8) {
        loadNextScene(scene);
        player->position.x.WORD = 8 << 16;
        if (player->position.y.HALF.HI > scene->mapHeightInMetatiles * MT_WIDTH - hBoxBOffset(hb) - 2)
            player->position.y.WORD = 245 << 16;
        return;
    }
    if (nextPos.y.HALF.HI < hBoxTOffset(hb) + 2) {
        nextPos.y.HALF.HI = hBoxTOffset(hb) + 2;
    }
    if (nextPos.y.HALF.HI > scene->mapHeightInMetatiles * MT_WIDTH - hBoxBOffset(hb) - 2) {
        nextPos.y.HALF.HI = scene->mapHeightInMetatiles * MT_WIDTH - hBoxBOffset(hb) - 2;
    }

    // update affine stuff
    updateEntityAffine(player);

    player->position.x = nextPos.x;
    player->position.y = nextPos.y;
    player->speed = speed;
}

Direction getDir(int direction[2], Direction dir) {
    switch ((direction[0] + 2) + 3 * (direction[1] + 2)) {
        case 4:     return NORTHWEST;
        case 7:     return WEST;
        case 10:    return SOUTHWEST;
        case 5:     return NORTH;
        case 11:    return SOUTH;
        case 6:     return NORTHEAST;
        case 9:     return EAST;
        case 12:    return SOUTHEAST;
        default:    return dir | STATIONARY;
    }
}

Direction getFacing(Entity* player) {
    switch (player->dir) {
        case EAST:
        case SOUTHEAST:
        case NORTHEAST:
            return EAST;
        case WEST:
        case SOUTHWEST:
        case NORTHWEST:
            return WEST;
        default:
            return player->facing;
    }
}

/** doesn't account for different collTypes yet */
Position handleCollision(Entity* player, union SplitWord normalisedSpeed, Position nextPos, u32 collision, Scene* scene) {
    Hitbox hb = player->hitbox;
    Position collidedPos = player->position;
    int xColl = (collision & X_COLL_MASK) > 0;
    int yColl = 2 * ((collision & Y_COLL_MASK) > 0);
    int cornerColl = 4 * ((collision & CORNER_COLL_MASK) > 0);

    int isPositiveX = (player->dir == EAST || player->dir == SOUTHEAST || player->dir == NORTHEAST) ? 1 : -1;
    int isPositiveY = (player->dir == SOUTH || player->dir == SOUTHWEST || player->dir == SOUTHEAST) ? 1 : -1;
    switch (xColl | yColl | cornerColl) {
        case 1: // xColl only
        case 5: // xColl + cornerColl
            nextPos.x.HALF.LO = 0;
            for (int i = 0; i < normalisedSpeed.HALF.HI; i++) {
                nextPos.x.HALF.HI -= isPositiveX;
                collision = getTileCollision(nextPos, player, scene);
                if ((collision & X_COLL_MASK) == 0) {
                    collidedPos.x = nextPos.x;
                    break;
                }
            }
            collidedPos.y = nextPos.y;
            break;
        case 2: // yColl only
        case 6: // yColl + cornerColl
            nextPos.y.HALF.LO = 0;
            for (int i = 0; i < normalisedSpeed.HALF.HI; i++) {
                nextPos.y.HALF.HI -= isPositiveY;
                collision = getTileCollision(nextPos, player, scene);
                if ((collision & Y_COLL_MASK) == 0) {
                    collidedPos.y = nextPos.y;
                    break;
                }
            }
            collidedPos.x = nextPos.x;
            break;
        case 7: // xColl + yColl  + cornerColl
            for (int i = 0; i < normalisedSpeed.HALF.HI; i++) {
                nextPos.y.HALF.HI -= isPositiveY;
                collision = getTileCollision(nextPos, player, scene);
                if ((collision & Y_COLL_MASK) == 0) {
                    collidedPos.y = nextPos.y;
                    break;
                }
            }
            for (int i = 0; i < normalisedSpeed.HALF.HI; i++) {
                nextPos.x.HALF.HI -= isPositiveX;
                collision = getTileCollision(nextPos, player, scene);
                if ((collision & X_COLL_MASK) == 0) {
                    collidedPos.x = nextPos.x;
                    break;
                }
            }
            break;
        case 4: // cornerColl only
            Position eastCollTest = { .x = {sWRound(collidedPos.x) + 0x20000}, .y = collidedPos.y };
            Position westCollTest = { .x = {sWRound(collidedPos.x) - 0x20000}, .y = collidedPos.y };
            Position southCollTest = { .x = collidedPos.x, .y = {sWRound(collidedPos.y) + 0x20000} };
            Position northCollTest = { .x = collidedPos.x, .y = {sWRound(collidedPos.y) - 0x20000} };
            u32 eastCollTop = getEdgeCollision(eastCollTest, hb, NORTHEAST, scene);
            u32 eastCollBottom = getEdgeCollision(eastCollTest, hb, SOUTHEAST, scene);
            u32 southCollLeft = getEdgeCollision(southCollTest, hb, SOUTHWEST, scene);
            u32 southCollRight = getEdgeCollision(southCollTest, hb, SOUTHEAST, scene);
            u32 westCollTop = getEdgeCollision(westCollTest, hb, NORTHWEST, scene);
            u32 westCollBottom = getEdgeCollision(westCollTest, hb, SOUTHWEST, scene);
            u32 northCollLeft = getEdgeCollision(northCollTest, hb, NORTHWEST, scene);
            u32 northCollRight = getEdgeCollision(northCollTest, hb, NORTHEAST, scene);
            bool isEastColl = ((eastCollTop + eastCollBottom) != 0);
            bool isSouthColl = 2 * ((southCollLeft + southCollRight) != 0);
            bool isWestColl = 4 * ((westCollTop + westCollBottom) != 0);
            bool isNorthColl = 8 * ((northCollLeft + northCollRight) != 0);
            switch (player->dir) {
                case NORTHEAST:
                    if (isNorthColl && isEastColl) break;
                    else if (isNorthColl) collidedPos.x = nextPos.x;
                    else if (isEastColl) collidedPos.y = nextPos.y;
                    break;
                case SOUTHEAST:
                    if (isSouthColl && isEastColl) break;
                    else if (isSouthColl) collidedPos.x = nextPos.x;
                    else if (isEastColl) collidedPos.y = nextPos.y;
                    break;
                case NORTHWEST:
                    if (isNorthColl && isWestColl) break;
                    else if (isNorthColl) collidedPos.x = nextPos.x;
                    else if (isWestColl) collidedPos.y = nextPos.y;
                    break;
                case SOUTHWEST:
                    if (isSouthColl && isWestColl) break;
                    else if (isSouthColl) collidedPos.x = nextPos.x;
                    else if (isWestColl) collidedPos.y = nextPos.y;
                    break;
                case EAST:
                    if (!isEastColl) collidedPos.x = nextPos.x;
                    if (eastCollTop) collidedPos.y.WORD += player->speed.WORD;
                    if (eastCollBottom) collidedPos.y.WORD -= player->speed.WORD;
                    break;
                case SOUTH:
                    if (!isSouthColl) collidedPos.y = nextPos.y;
                    if (southCollLeft) collidedPos.x.WORD += player->speed.WORD;
                    if (southCollRight) collidedPos.x.WORD -= player->speed.WORD;
                    break;
                case WEST:
                    if (!isWestColl) collidedPos.x = nextPos.x;
                    if (westCollTop) collidedPos.y.WORD += player->speed.WORD;
                    if (westCollBottom) collidedPos.y.WORD -= player->speed.WORD;
                    break;
                case NORTH:
                    if (!isNorthColl) collidedPos.y = nextPos.y;
                    if (northCollLeft) collidedPos.x.WORD += player->speed.WORD;
                    if (northCollRight) collidedPos.x.WORD -= player->speed.WORD;
                    break;
                default:
                    break;
            }
            break;
        case 0:
            collidedPos = nextPos;
            break;
        default:
            break;
    }
    return collidedPos;
}

void updateEntityAffine(Entity* player) {
    switch (player->facing) {
        case EAST:
            obj_aff_rotscale(player->obj_aff, 256, 256, player->rotation.WORD);
            break;
        case WEST:
            obj_aff_rotscale(player->obj_aff, -256, 256, player->rotation.WORD);
            break;
        default:
            break;
    }
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
    static int waitFrames = 0;
    static int numOfSpinInputs = 0;
    if (waitFrames == SPIN_WAIT_FRAMES) {
        waitFrames = 0;
        numOfSpinInputs = 0;
        return false;
    }
    if (numOfSpinInputs == 8) {
        waitFrames = 0;
        numOfSpinInputs = 0;
        return true;
    }
    Direction dirMod = dir % 4;
    if (numOfSpinInputs == 0) {
        spinArray[0] = dirMod;
        numOfSpinInputs++;
        return false;
    }
    spinArray[numOfSpinInputs] = (dirMod == spinArray[numOfSpinInputs - 1] + 1) ||
        (dirMod == spinArray[numOfSpinInputs - 1] - 3) ? dirMod : 8;
    if (spinArray[numOfSpinInputs] != 8) {
        waitFrames = 0;
        numOfSpinInputs++;
    }
    else {
        waitFrames++;
    }
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

// Direction getDir(int direction[2], Direction dir) // old, cool, pointless
// {
//     if ((direction[0] || direction[1]) == 0) return dir | 8; // unchanged, with stationary bit set
//     // check whether diagonal
//     int newDir = 0 | (direction[0] && direction[1]) << 2;

//     // check cardinal direction (rotated clockwise 45deg if diagonal except NE and NW are swapped)
//     switch (direction[0])
//     {
//         case 1: // E, SE, NW
//             newDir |= (newDir >> 2) - direction[1];
//             break;
//         default: // N, S, W, SW, NE. direction[0] = 0, -1
//             newDir |= 2 - direction[1]; // only if dpad is pressed
//             break;
//     }
//     return newDir;
// }
