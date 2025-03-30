#ifndef playerh
#define playerh

#include "entity.h"
#include "scene.h"
#include "initialise.h"
#include "type.h"
#include "constants.h"

void handleInput();
Direction getDir(int direction[2], Direction dir);
Position getNextPosition(Entity* ent);
void updateEntityAffine(Entity* ent);
void dig(Entity* ent, Scene* scene);
void updateAttacks();
bool checkForSpin(Direction dir);
void updatePlayerAnimation(Entity* ent, u8 prevAnimState);
int getNextDiffX(int x, union SplitWord speed, u32 angle);
int getNextDiffY(int y, union SplitWord speed, u32 angle);
u16 getAngle(Direction dir, u32 angle);
union SplitWord handleCollisionX(Entity* ent);
union SplitWord handleCollisionY(Entity* ent);

#endif
