#ifndef scrollh
#define scrollh

#include "entity.h"
#include "initialise.h"
#include "constants.h"
#include "type.h"

void handleScroll();
void moveScreenOnMap(Entity* ent, Scene* scene);
void movePlayerSpriteOnScreen(Entity* player, Position pos);
void moveSpriteOnScreen(Entity* ent, Position offset);
bool checkIfOnScreen(Entity* ent);

#endif
