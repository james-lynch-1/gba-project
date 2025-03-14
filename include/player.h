#ifndef playerh
#define playerh

#include "entity.h"
#include "initialise.h"

void handleInput();
Direction getDir(int direction[2], Direction dir);
Direction getFacing(Entity* ent);
void updateAnimations(Entity* ent);
Position handleCollision(Entity* ent, union SplitWord normalisedSpeed, Position nextPos, u32 collision, Scene* scene);
u32 getCollisionMinusI(Entity* ent, union SplitWord normalisedSpeed, int i, Position nextPos, u32 collision, Scene* scene);
void updateEntityAffine(Entity* ent);
void dig(Entity* ent, Scene* scene);

void updateAttacks();

bool checkForSpin(Direction dir);

void updatePlayerAnimation(Entity* ent, u8 prevAnimState);

#endif
