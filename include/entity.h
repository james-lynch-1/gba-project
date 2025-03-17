#ifndef entityh
#define entityh

#include <tonc.h>
#include "type.h"
#include "scene.h"
#include "tile.h"
#include "constants.h"
#include "ui.h"
#include "attacks.h"

// collision direction masks to get direction from a collision bitfield

#define E_COLL_MASK      0x0000000Fu
#define S_COLL_MASK      0x000000F0u
#define W_COLL_MASK      0x00000F00u
#define N_COLL_MASK      0x0000F000u
#define SE_COLL_MASK     0x000F0000u
#define SW_COLL_MASK     0x00F00000u
#define NE_COLL_MASK     0x0F000000u
#define NW_COLL_MASK     0xF0000000u

#define PACKED_COLLMAP_MASK 0x0000000Fu

#define X_COLL_MASK      0X00000F0Fu
#define Y_COLL_MASK      0x0000F0F0u

#define CORNER_COLL_MASK 0xFFFF0000u
#define COLL_MASK        0xFFFFFFFFu

// animation state
#define ANIM_IDLE           0
#define ANIM_HURT           1
#define ANIM_WALK           2

// ilks
#define ILK_PLAYER  0
#define ILK_FELLA   1

typedef struct Hitbox_ {
    u8 width;
    u8 height;
    s8 leftOffset; // offset from pos.x to get left edge coord
    s8 rightOffset; // offset from pos.x to get right edge coord
    s8 topOffset; // offset from pos.y to get top edge coord
    s8 bottomOffset; // offset from pos.y to get bottom edge coord
    s8 xOffset; // whole hitbox offset on x axis
    s8 yOffset; // whole hitbox offset on y axis
} Hitbox;

typedef struct Entity_ {
    // linked list
    struct Entity_* prev; // 4 bytes
    struct Entity_* next; // 4 bytes
    bool toBeDeleted; // 4 bytes

    // shadow OAM entries
    OBJ_ATTR* obj; // 4 bytes
    OBJ_AFFINE* obj_aff; // 4 bytes

    // important
    void (*moveSprite)(struct Entity_* ent, Position offset); // 4 bytes
    int health; // 4 bytes
    Position position; // 8 bytes
    Hitbox hitbox; // 8 bytes
    union SplitWord speed; // 4 bytes
    union SplitWord rotation; // 4 bytes
    Direction dir; // 4 bytes
    u16 tid; // 2 bytes
    u16 remoteControlCountdown; // 2 bytes. No. of frames before control is handed back to the player. 65535 means indefinite
    AttackInstance* attacksActive; // 4 bytes
    u8 affIndex; // 1 byte
    u8 ilk; // 1 byte
    u8 invincibleTime; // 1 byte

    // visual
    u8 pb; // 1 byte
    u8 animationState; // 1 byte
    u8 facing; // 1 byte
    u8 facingLocked; // 1 byte
    u8 animFrames; // 1 byte. how many frames ent has been in current animation state
    u8 width; // 1 byte
    u8 height; // 1 byte
    u8 spriteShape; // 1 byte, needs to be shifted left by 12 to be used in OAM
    u8 spriteSize; // 1 byte, needs to be shifted left by 12 to be used in OAM
    u8 spriteType; // 1 byte, needs to be shifted left by ATTR0_MODE_SHIFT (8) to be used in OAM
} Entity;

// Collision data for 16 metatiles (1 SBB row / 1 32 tile-wide map) packed into two words.
// 4 bits/tile -> 16 possible collision types per tile
typedef union __attribute__((packed)) CollisionTileRow_ {
    struct row {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
    } row;
    u32 halfSBBRow[2];
} CollisionTileRow;

/** Collision data for 32 metatiles (2 SBB rows / 1 64 tile-wide map) packed into four words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRowDbl_ {
    struct rowDbl {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
        u8 t16 : 4; u8 t17 : 4; u8 t18 : 4; u8 t19 : 4; u8 t20 : 4; u8 t21 : 4; u8 t22 : 4; u8 t23 : 4;
        u8 t24 : 4; u8 t25 : 4; u8 t26 : 4; u8 t27 : 4; u8 t28 : 4; u8 t29 : 4; u8 t30 : 4; u8 t31 : 4;
    } row;
    u32 halfSBBRow[4];
} CollisionTileRowDbl;

Entity* loadPlayer();

Entity* loadEnt();

void spawnFella(Position pos);

void updateEnts();

void deleteEnt(Entity* ent);

void deleteNextAtkInstance(AttackInstance* atkInst);

void pushNewAttack(Attack* atk);

u32 checkCrosshairEntColl(Entity* ent, Position crosshairWorldPos);

void handlePlayerAttacks(Entity* ent, int crosshairEntColl);

// void handleCrosshairEntColl(Entity* ent, int crosshairEntColl);

void doAttack(Entity* ent, u8 attackRangeValue);

void updateAnimation(Entity* ent, u8 prevAnimState);

bool checkPlayerEntCollision(Entity* player, Entity* currEnt);

void doPlayerKnockback(Entity* ent);

int hBoxLOffset(Hitbox hitbox);
int hBoxROffset(Hitbox hitbox);
int hBoxTOffset(Hitbox hitbox);
int hBoxBOffset(Hitbox hitbox);
int hBoxXOffset(Hitbox hitbox);
int hBoxYOffset(Hitbox hitbox);

// collision

u32 getTileCollision(Position nextPos, Entity* ent, Scene* scene);
int getTileCollisionPoint(int point[2], Scene* scene);
u32 getEdgeCollision(Position nextPos, Hitbox hitbox, Direction dir, Scene* scene);

#endif
