#ifndef sceneh
#define sceneh

#include "log.h"
#include "entity.h"
#include "constants.h"
#include "type.h"
#include "tile.h"

const extern struct SceneData sceneDataArr[NUM_SCENES];

void loadScene(Scene* currScene, SceneEnum sceneName);
void unloadScene(Scene* scene);
void loadBG(const u16* pal, int palLen, const u16* tiles, int tilesLen, const u16* map, int mapLen, Scene* scene);
void copyTileCol(Scene* scene, int tileX, int tileY);
void copyTileRow(Scene* scene, int tileX, int tileY);

// scroll methods
void handleScroll();
void moveViewportOnMap(Entity* ent, Scene* scene);
void movePlayerSpriteOnScreen(Entity* player, Position pos);
void moveSpriteOnScreen(Entity* ent, Position offset);
bool checkIfOnScreen(Entity* ent);
void updateBGTiles(Scene* scene);

bool mTileIsWithinViewport(Position pos, Viewport vp);

#endif
