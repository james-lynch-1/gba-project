#include "entity.h"
#include "log.h"
#include "global.h"

Entity* loadPlayer() {
    Entity* entities = malloc(sizeof(Entity));
    Entity player =
    {
        .prev = NULL,
        .next = NULL,
        .health = 255,
        .position.x.HALF.HI = 64,
        .position.y.HALF.HI = 64,
        .radius.WORD = 0x1C000,
        .angleOffset = 0xC000,
        .angle = 0x4000,
        .animationState = ANIM_IDLE,
        .animFrames = 0,
        .attacksActive = NULL,
        .obj = &obj_buffer[1],
        .obj_aff = &obj_aff_buffer[0],
        .moveSprite = movePlayerSpriteOnScreen,
        .hitbox = playerHitbox,
        .spriteShape = ATTR0_SQUARE >> 12,
        .spriteSize = ATTR1_SIZE_32 >> 12,
        .objectMode = ATTR0_AFF >> ATTR0_MODE_SHIFT,
        .affIndex = ATTR1_AFF_ID(0),
        .tid = 0,
        .pb = 0,
        .ilk = PLAYER,
    };
    *entities = player;
    obj_set_attr(entities->obj,
        entities->spriteShape << 12 | entities->objectMode << ATTR0_MODE_SHIFT,
        entities->spriteSize << 12 | entities->affIndex,
        ATTR2_PRIO(3) | ATTR2_PALBANK(entities->pb) | entities->tid);
    numEnts++;
    return entities;
}

/** assumes one ent (player) already exists */
Entity* loadEnt() {
    if (numEnts >= 16) {
        log(CHAR, "numEnts at maximum");
        return NULL;
    }
    Entity* currEnt = entities;
    Entity* prevEnt = currEnt;
    while (currEnt != NULL) {
        prevEnt = currEnt;
        currEnt = currEnt->next;
    }
    currEnt = malloc(sizeof(Entity));
    prevEnt->next = currEnt;
    Entity newEnt =
    {
        .prev = prevEnt,
        .next = NULL,
        .obj = &obj_buffer[numEnts + 1],
        .obj_aff = NULL
    };
    *currEnt = newEnt;
    numEnts++;
    return currEnt;
}

void spawnFella(Position pos) {
    Entity* fella = loadEnt();
    if (fella) {
        fella->position = pos;
        fella->width = 8;
        fella->height = 8;
        fella->health = 120;
        fella->animationState = ANIM_IDLE;
        fella->ilk = FELLA;
        fella->tid = 64;
        fella->pb = 1;
        fella->spriteShape = ATTR0_SQUARE;
        fella->spriteSize = ATTR1_SIZE_8;
        fella->objectMode = ATTR0_REG;
        fella->affIndex = 0;
        fella->moveSprite = moveSpriteOnScreen;
        fella->hitbox = fellaHitbox;
        obj_set_attr(fella->obj,
            fella->spriteShape | ATTR0_REG,
            fella->spriteSize,
            ATTR2_PRIO(3) | ATTR2_PALBANK(fella->pb) | ATTR2_ID(fella->tid));
    }
}

/** Updates animation frames, affine data (TBC), positions on screen, health */
void updateEnts() {
    Position crosshairWorldPos = screenToWorldPos(crosshairPos);
    Entity* currEnt = entities->next; // not updating the player, handled elsewhere
    int numEntsOnScreen = 2;
    while (currEnt != NULL) {
        Entity* next = currEnt->next;
        if (currEnt->toBeDeleted) {
            deleteEnt(currEnt);
            currEnt = next;
        }
        else {
            bool onScreen = checkIfOnScreen(currEnt);
            if (onScreen) {
                currEnt->obj = &obj_buffer[numEntsOnScreen++];
                u8 prevAnimState = currEnt->animationState;
                Position offset = { {0}, {0} };
                currEnt->moveSprite(currEnt, offset);
                int crosshairEntColl = checkCrosshairEntColl(currEnt, crosshairWorldPos);
                handlePlayerAttacks(currEnt, crosshairEntColl);
                updateAnimation(currEnt, prevAnimState);
                if (!entities->invincibleTime && checkPlayerEntCollision(entities, currEnt))
                    doPlayerKnockback(currEnt);
            }
            if (currEnt->health <= 0)
                currEnt->toBeDeleted = 1;
            currEnt = next;
        }
    }
    for (int i = numEntsOnScreen; i < 128; i++)
        obj_set_attr(&obj_buffer[i], 0, 0, 0);
}

void markAllEntsToBeDeleted() {
    Entity* ent = entities->next;
    while (ent) {
        ent->toBeDeleted = 1;
        ent = ent->next;
    }
}

void deleteEnt(Entity* ent) {
    obj_set_attr(ent->obj, 0, 0, 0);
    (ent->prev)->next = ent->next;
    if (ent->next) (ent->next)->prev = ent->prev;
    free(ent);
    numEnts--;
}

/** returns crosshair-ent collision
 * (can be either a dead-on collision (Highest value),
 *  single-axis collision (Medium value), or
 *  quadrant collision (lowest value under most circumstances)) */
u32 checkCrosshairEntColl(Entity* ent, Position crosshairWorldPos) {
    // NW, SE
    Position entCornerPositions[2] = { {.x.HALF.HI = ent->position.x.HALF.HI + ent->hitbox.leftOffset,
                                        .y.HALF.HI = ent->position.y.HALF.HI + ent->hitbox.topOffset},
                                       {.x.HALF.HI = ent->position.x.HALF.HI + ent->hitbox.rightOffset + 1,
                                        .y.HALF.HI = ent->position.y.HALF.HI + ent->hitbox.bottomOffset + 1} };
    int isInE = entCornerPositions[1].x.WORD > crosshairWorldPos.x.WORD;
    int isInS = 2 * (entCornerPositions[1].y.WORD > crosshairWorldPos.y.WORD);
    int isInW = 4 * (entCornerPositions[0].x.WORD < crosshairWorldPos.x.WORD);
    int isInN = 8 * (entCornerPositions[0].y.WORD < crosshairWorldPos.y.WORD);
    switch (isInE + isInS + isInW + isInN) {
        case 11: return ATK_E_COLL;
        case 7: return ATK_S_COLL;
        case 14: return ATK_W_COLL;
        case 13: return ATK_N_COLL;
        case 3: return ATK_SE_COLL;
        case 6: return ATK_SW_COLL;
        case 12: return ATK_NW_COLL;
        case 9: return ATK_NE_COLL;
        case 15: return ATK_CTR_COLL;
        default: return 0;
    }
}

void updateAnimation(Entity* ent, u8 prevAnimState) {
    u8 frames = ent->animFrames;
    Position offset = { {0}, {0} };
    if (ent->animationState != prevAnimState) {
        frames = 0;
    }
    switch (ent->animationState) {
        case ANIM_IDLE:
            ent->obj->attr2 = ATTR2_PRIO(3) | ATTR2_PALBANK(ent->pb) | ent->tid;
            break;
        case ANIM_HURT:
            offset.x.HALF.HI = qran_range(-3, 3);
            offset.y.HALF.HI = qran_range(-3, 3);
            break;
        case ANIM_WALK:
            switch (frames) {
                case 32:
                    frames = 0;
                case 0:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(0) | ATTR2_PALBANK(ent->pb);
                    break;
                case 8:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(16) | ATTR2_PALBANK(ent->pb);
                    break;
                case 16:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(32) | ATTR2_PALBANK(ent->pb);
                    break;
                case 24:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(48) | ATTR2_PALBANK(ent->pb);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    ent->moveSprite(ent, offset);
    frames++;
    ent->animFrames = frames;
}

/** checks ent-player collision and returns the direction mask u32 */
bool checkPlayerEntCollision(Entity* player, Entity* ent) { // broad to narrow
    // first check which sides hitboxes overlap on, if any
    u32 xColl = 0;
    u32 yColl = 0;
    if (player->position.x.HALF.HI >= ent->position.x.HALF.HI) { // player to the right
        xColl = (((player->position.x.HALF.HI + hBoxLOffset(player->hitbox) <
            ent->position.x.HALF.HI + hBoxROffset(ent->hitbox))) << 8); // W_COLL_MASK 0x0F00u
    }
    else { // player to the left
        xColl = (((player->position.x.HALF.HI + hBoxROffset(player->hitbox) >
            ent->position.x.HALF.HI + hBoxLOffset(ent->hitbox))) << 0); // E_COLL_MASK 0x0000u
    }
    if (xColl == 0) return 0; // no need to continue if no overlap on one of the axes
    if (player->position.y.HALF.HI >= ent->position.y.HALF.HI) { // player below
        yColl = (((player->position.y.HALF.HI + hBoxTOffset(player->hitbox) <
            ent->position.y.HALF.HI + hBoxBOffset(ent->hitbox))) << 12); // N_COLL_MASK 0xF000u
    }
    else { // player above
        yColl = (((player->position.y.HALF.HI + hBoxBOffset(player->hitbox) >
            ent->position.y.HALF.HI + hBoxTOffset(ent->hitbox))) << 4); // S_COLL_MASK 0x00F0u
    }
    if (yColl == 0) return 0;
    return 1;
}

void doPlayerKnockback(Entity* ent) {
    Entity* player = entities;
    player->remoteControlCountdown = 4;
    player->invincibleTime = 61;
    player->angle = (player->angle + 0x8000) & 0xFFFF;
    return;
}

int hBoxLOffset(Hitbox hb) {
    return hb.leftOffset + hb.xOffset;
}

int hBoxROffset(Hitbox hb) {
    return hb.rightOffset + hb.xOffset;
}

int hBoxTOffset(Hitbox hb) {
    return hb.topOffset + hb.yOffset;
}

int hBoxBOffset(Hitbox hb) {
    return hb.bottomOffset + hb.yOffset;
}

int hBoxXOffset(Hitbox hb) {
    return hb.xOffset;
}

int hBoxYOffset(Hitbox hb) {
    return hb.yOffset;
}

Position screenToWorldPos(Position pos) {
    Position worldPos = { {(pos.x.HALF.HI + vp.x) << 16}, {(pos.y.HALF.HI + vp.y) << 16} };
    return worldPos;
}
