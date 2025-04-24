#ifndef playerh
#define playerh

#include <tonc.h>
#include "entity.h"
#include "scene.h"
#include "initialise.h"
#include "type.h"
#include "constants.h"
#include "global.h"

void handleInput();
Direction getDir(int direction[2], Direction dir);
Position getNextPosition(Entity* ent);
void updateEntityAffine(Entity* ent);
void dig(Entity* ent, Scene* scene);
void updateAttacks();
bool checkForSpin(Direction dir);
void setSpin(Direction* prevDir, Direction newDir, int* waitFrames, int newWF, int* numSpinputs, int newNS);
void updatePlayerAnimation(Entity* ent, u8 prevAnimState);
int getNextDiffX(int x, SWord speed, u32 angle);
int getNextDiffY(int y, SWord speed, u32 angle);
u16 getAngle(Direction dir, u32 angle);
SWord handleCollisionX(Entity* ent);
SWord handleCollisionY(Entity* ent);
int decaySpeed(SWord speed, SWord radius);

#endif
