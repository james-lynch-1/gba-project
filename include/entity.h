#ifndef entityh
#define entityh

#include <tonc.h>
#include "type.h"
#include "scene.h"
#include "tile.h"
#include "constants.h"
#include "ui.h"
#include "attacks.h"
#include "stdlib.h"

// collision direction masks to get direction from a collision bitfield

#define X_CNTR_COLL_MASK    0x000000F0u
#define Y_CNTR_COLL_MASK    0x000F0000u
#define X_COLL_MASK         0x00000FFFu
#define Y_COLL_MASK         0x00FFF000u
#define X_CRNR_COLL_MASK    0x00000F0Fu
#define Y_CRNR_COLL_MASK    0x00F0F000u
#define X_CRNR_COLL_1_MASK  0x0000000Fu
#define X_CRNR_COLL_2_MASK  0x00000F00u
#define Y_CRNR_COLL_1_MASK  0x0000F000u
#define Y_CRNR_COLL_2_MASK  0x00F00000u

#define PACKED_COLLMAP_MASK 0x0000000Fu
#define CORNER_COLL_MASK    0x00F0FF0Fu
#define COLL_MASK        0xFFFFFFFFu

// animation state
#define ANIM_IDLE           0
#define ANIM_HURT           1
#define ANIM_WALK           2

// ilks
#define ILK_PLAYER  0
#define ILK_FELLA   1

/** Collision data for 16 metatiles (1 SBB row / 1 32 tile-wide map) packed into two words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRow256x256_ {
    struct row {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
    } row;
    u32 halfSBBRow[2];
} CollisionTileRow256x256;

/** Collision data for 32 metatiles (2 SBB rows / 1 64 tile-wide map) packed into four words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRow512x512_ {
    struct rowDbl {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
        u8 t16 : 4; u8 t17 : 4; u8 t18 : 4; u8 t19 : 4; u8 t20 : 4; u8 t21 : 4; u8 t22 : 4; u8 t23 : 4;
        u8 t24 : 4; u8 t25 : 4; u8 t26 : 4; u8 t27 : 4; u8 t28 : 4; u8 t29 : 4; u8 t30 : 4; u8 t31 : 4;
    } row;
    u32 halfSBBRow[4];
} CollisionTileRow512x512;

/** Collision data for 64 metatiles (4 SBB rows / 1 128 tile-wide map) packed into eight words.
4 bits/tile -> 16 possible collision types per tile */
typedef union __attribute__((packed)) CollisionTileRow1024x1024_ {
    struct rowQdrpl {
        u8 t0 : 4; u8 t1 : 4; u8 t2 : 4; u8 t3 : 4; u8 t4 : 4; u8 t5 : 4; u8 t6 : 4; u8 t7 : 4;
        u8 t8 : 4; u8 t9 : 4; u8 t10 : 4; u8 t11 : 4; u8 t12 : 4; u8 t13 : 4; u8 t14 : 4; u8 t15 : 4;
        u8 t16 : 4; u8 t17 : 4; u8 t18 : 4; u8 t19 : 4; u8 t20 : 4; u8 t21 : 4; u8 t22 : 4; u8 t23 : 4;
        u8 t24 : 4; u8 t25 : 4; u8 t26 : 4; u8 t27 : 4; u8 t28 : 4; u8 t29 : 4; u8 t30 : 4; u8 t31 : 4;
        u8 t32 : 4; u8 t33 : 4; u8 t34 : 4; u8 t35 : 4; u8 t36 : 4; u8 t37 : 4; u8 t38 : 4; u8 t39 : 4;
        u8 t40 : 4; u8 t41 : 4; u8 t42 : 4; u8 t43 : 4; u8 t44 : 4; u8 t45 : 4; u8 t46 : 4; u8 t47 : 4;
        u8 t48 : 4; u8 t49 : 4; u8 t50 : 4; u8 t51 : 4; u8 t52 : 4; u8 t53 : 4; u8 t54 : 4; u8 t55 : 4;
        u8 t56 : 4; u8 t57 : 4; u8 t58 : 4; u8 t59 : 4; u8 t60 : 4; u8 t61 : 4; u8 t62 : 4; u8 t63 : 4;
    } row;
    u32 halfSBBRow[8];
} CollisionTileRow1024x1024;

// entities
Entity* loadPlayer();
Entity* loadEnt();
void spawnFella(Position pos);
void updateEnts();
void deleteEnt(Entity* ent);

// attacks
void deleteNextAtkInstance(AttackInstance* atkInst);
void pushNewAttack(Attack* atk);
u32 checkCrosshairEntColl(Entity* ent, Position crosshairWorldPos);
void handlePlayerAttacks(Entity* ent, int crosshairEntColl);
void doAttack(Entity* ent, u8 attackRangeValue);
void updateAnimation(Entity* ent, u8 prevAnimState);
bool checkPlayerEntCollision(Entity* player, Entity* currEnt);
void doPlayerKnockback(Entity* ent);

// hitbox
int hBoxLOffset(Hitbox hitbox);
int hBoxROffset(Hitbox hitbox);
int hBoxTOffset(Hitbox hitbox);
int hBoxBOffset(Hitbox hitbox);
int hBoxXOffset(Hitbox hitbox);
int hBoxYOffset(Hitbox hitbox);

// collision
u32 getPointCollision(Position pos, Scene* scene);
u32 getEdgePointCollision(Position nextPos, Hitbox hb, Direction dir, Scene* scene);
u32 getEdgeCollision(Position pos, Hitbox hb, Direction cardDir, Scene* scene);

#endif
