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
#include "hitbox.h"

// ilks
#define PLAYER  0
#define FELLA   1

extern u32(* const getPointCollFns[])(Position pos, void* collisionMap);
extern u32(* const handlePointCollFns[])(Position pos, u32 tileColl);
extern TileCollArray TileCollArrays[16];

// entities
Entity* loadPlayer();
Entity* loadEnt();
void spawnFella(Position pos);
void updateEnts();
void markAllEntsToBeDeleted();
void deleteEnt(Entity* ent);

// attacks
u32 checkCrosshairEntColl(Entity* ent, Position crosshairWorldPos);
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

Position screenToWorldPos(Position pos);

// collision
u32 getPointCollision256x256(Position pos, void* collisionMap);
u32 getPointCollision512x512(Position pos, void* collisionMap);
u32 getPointCollision1024x1024(Position pos, void* collisionMap);
u32 getEdgePointCollision(Position nextPos, Hitbox hb, Direction dir, Scene* scene);
u32 getEdgeCollision(Position pos, Hitbox hb, Direction cardDir, Scene* scene);

u32 getInTilePointColl(Position pos, u32 tileColl);
u32 handleItemTileColl(Position pos, u32 tileColl);
int doAction(int actionTileId);
u32 handleActionTileColl(Position pos, u32 tileColl);

#endif
