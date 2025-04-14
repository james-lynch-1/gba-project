#ifndef initialiseh
#define initialiseh

#include <tonc.h>
#include <stdlib.h>
#include "scene.h"

void initialise();
void loadUI();
void loadSprites();
void loadTiles();
Scene* loadSceneInitial(SceneEnum sceneName);

#endif
