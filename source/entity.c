#include "entity.h"
#include "log.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE* obj_aff_buffer;
extern Entity* entities;
extern Scene* scene;
extern int numEnts;
extern Position crosshairPos;
extern void moveSpriteOnScreen();
extern void movePlayerSpriteOnScreen();
extern bool checkIfOnScreen();
extern int numAttacks;
extern u32 frameCount;

Entity* loadPlayer() {
    Entity* entities = malloc(sizeof(Entity));
    Entity player =
    {
        .prev = NULL,
        .next = NULL,
        .health = 255,
        .position.x.HALF.HI = 64,
        .position.y.HALF.HI = 64,
        .speed.HALF.HI = 1,
        .dir = EAST,
        .animationState = ANIM_IDLE,
        .facing = EAST,
        .animFrames = 0,
        .obj = &obj_buffer[0],
        .obj_aff = &obj_aff_buffer[0],
        .moveSprite = movePlayerSpriteOnScreen,
        .rotation = {0},
        .facingLocked = 0,
        .hitbox =
        {
            .width = 15, .height = 12,
            .leftOffset = -7, .rightOffset = 7,
            .topOffset = -6, .bottomOffset = 5,
            .xOffset = 0, .yOffset = 4
        },
        .spriteShape = ATTR0_SQUARE >> 12,
        .spriteSize = ATTR1_SIZE_32 >> 12,
        .spriteType = ATTR0_AFF >> ATTR0_MODE_SHIFT,
        .affIndex = ATTR1_AFF_ID(0),
        .tid = 0,
        .pb = 0,
        .ilk = ILK_PLAYER,
    };
    *entities = player;
    obj_set_attr(entities->obj,
        entities->spriteShape << 12 | entities->spriteType << ATTR0_MODE_SHIFT,
        entities->spriteSize << 12 | entities->affIndex,
        ATTR2_PRIO(3) | ATTR2_PALBANK(entities->pb) | entities->tid);
    numEnts++;
    return entities;
}

/** assumes one ent (player) already exists */
Entity* loadEnt() {
    if (numEnts >= 16) {
        mgbaLog(CHAR VA "numEnts at maximum");
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
        .obj = &obj_buffer[numEnts],
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
        fella->ilk = ILK_FELLA;
        fella->tid = 48;
        fella->pb = 1;
        fella->spriteShape = ATTR0_SQUARE;
        fella->spriteSize = ATTR1_SIZE_8;
        fella->spriteType = ATTR0_REG;
        fella->affIndex = 0;
        fella->moveSprite = moveSpriteOnScreen;
        fella->facingLocked = 0;
        Hitbox hitbox = { .width = 8, .height = 8, .leftOffset = -4, .rightOffset = 3,
                          .topOffset = -4, .bottomOffset = 3, .xOffset = 0, .yOffset = 0 };
        fella->hitbox = hitbox;
        obj_set_attr(fella->obj,
            fella->spriteShape | ATTR0_REG,
            fella->spriteSize,
            ATTR2_PRIO(3) | ATTR2_PALBANK(fella->pb) | ATTR2_ID(fella->tid));
    }
}

/** Updates animation frames, affine data (TBC), positions on screen, health */
void updateEnts() {
    Position crosshairWorldPos = { .x.HALF.HI = crosshairPos.x.HALF.HI + scene->screenX,
                                   .y.HALF.HI = crosshairPos.y.HALF.HI + scene->screenY };
    Entity* currEnt = entities->next; // not updating the player, handled elsewhere
    while (currEnt != NULL) {
        Entity* next = currEnt->next;
        if (currEnt->toBeDeleted) {
            deleteEnt(currEnt);
            currEnt = next;
        }
        else {
            bool onScreen = checkIfOnScreen(currEnt);
            if (onScreen) {
                u8 prevAnimState = currEnt->animationState;
                currEnt->obj->attr0 &= ~ATTR0_HIDE;
                // currEnt->animationState = ANIM_IDLE;
                Position offset = { {0}, {0} };
                currEnt->moveSprite(currEnt, offset);
                int crosshairEntColl = checkCrosshairEntColl(currEnt, crosshairWorldPos);
                handlePlayerAttacks(currEnt, crosshairEntColl);
                updateAnimation(currEnt, prevAnimState);
                if (!entities->invincibleTime) {
                    if (checkPlayerEntCollision(entities, currEnt)) doPlayerKnockback(currEnt);
                }
            }
            else currEnt->obj->attr0 |= ATTR0_HIDE;
            if (currEnt->health <= 0) {
                currEnt->toBeDeleted = true;
            }
            currEnt = next;
        }
    }
}

void deleteEnt(Entity* ent) {
    obj_set_attr(ent->obj, 0, 0, 0);
    (ent->prev)->next = ent->next;
    if (ent->next) (ent->next)->prev = ent->prev;
    free(ent);
    numEnts--;
}

void deleteNextAtkInstance(AttackInstance* atkInst) {
    AttackInstance* toBeDeleted = atkInst->next;
    atkInst = toBeDeleted->next;
    free(toBeDeleted);
}

void pushNewAttack(Attack* atk) {
    if (numAttacks < 4) {
        AttackInstance* atkInstPtr = malloc(sizeof(AttackInstance));
        AttackInstance atkInst = {
            .next = NULL,
            .attack = atk,
            .timer = atk->countdown + atk->duration
        };
        *atkInstPtr = atkInst;
        AttackInstance* slot = entities->attacksActive;
        while (slot != NULL && slot->next != NULL) {
            slot = slot->next;
        }
        if (slot == NULL) entities->attacksActive = atkInstPtr;
        else slot->next = atkInstPtr;
        numAttacks++;
    }
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
    int coll = isInE + isInS + isInW + isInN;
    return coll;
}

void handlePlayerAttacks(Entity* ent, int crosshairEntColl) {
    ent->animationState = ANIM_IDLE;
    Entity player = *entities;
    AttackInstance* atkInst = player.attacksActive;
    while (atkInst != NULL) {
        for (int i = 0; i < MAX_ATK_RANGE; i++) {
            if (atkInst->attack->range[i] == 0) break;
            if (atkInst->attack->range[i] == crosshairEntColl && atkInst->timer <= atkInst->attack->duration) {
                basicAttack(ent, atkInst);
                break; // only one crosshairEntColl per ent, after all
            }
        }
        atkInst = atkInst->next;
    }
}

// void handleCrosshairEntColl(Entity* ent, int crosshairEntColl) {
//     ent->animationState = ANIM_IDLE;
//     switch (crosshairEntColl) {
//         case ATK_SE_COLL: // SE
//             // mgbaLog(CHAR VA "SE");
//             // if in a special attack state, take appropriate damage
//             // same for other quadrants/directions
//             break;
//         case ATK_NE_COLL: // NE
//             // mgbaLog(CHAR VA "NE");
//             break;
//         case ATK_SW_COLL: // SW
//             // mgbaLog(CHAR VA "SW");
//             break;
//         case ATK_NW_COLL: // NW
//             // mgbaLog(CHAR VA "NW");
//             break;
//         case ATK_S_COLL: // E+S+W
//             // mgbaLog(CHAR VA "S");
//             break;
//         case ATK_E_COLL: // E+S+N
//             // mgbaLog(CHAR VA "E");
//             break;
//         case ATK_N_COLL: // E+W+N
//             // mgbaLog(CHAR VA "N");
//             break;
//         case ATK_W_COLL: // S+W+N
//             // mgbaLog(CHAR VA "W");
//             break;
//         case ATK_CTR_COLL: // centre
//             basicAttack(ent);
//             mgbaLog(U32 VA ent->health);
//             break;
//         default: break;
//     }
// }

void basicAttack(Entity* ent, AttackInstance* atkInst) {
    ent->animationState = ANIM_HURT;
    ent->health -= atkInst->attack->dmg;
}

// void quadrantAttack(Entity* ent) {
//     while (entities->attacksActive != NULL) {

//     }
// }

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
                case 25:
                    frames = 0;
                case 0:
                case 17:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(0) | ATTR2_PALBANK(ent->pb);
                    break;
                case 1:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(16) | ATTR2_PALBANK(ent->pb);
                    break;
                case 9:
                    ent->obj->attr2 &= ATTR2_ID(!ATTR2_ID_MASK);
                    ent->obj->attr2 |= ATTR2_ID(32) | ATTR2_PALBANK(ent->pb);
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
    entities->remoteControlCountdown = 4;
    entities->invincibleTime = 61;
    entities->facingLocked = 1;
    if (entities->dir != STATIONARY) {
        entities->dir = (entities->dir & DIAGONAL) | ((entities->dir + 2) % 4); // change to opposite direction
    }
    else entities->dir = ent->dir;
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
