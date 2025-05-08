#ifndef initialiseh
#define initialiseh

#include <tonc.h>
#include <stdlib.h>
#include "scene.h"
#include "entity.h"
#include "global.h"
#include "graphics/graphics.h"

void initialise();
void switchGameState(GameStateEnum gStateEnum);
void enterNormalState();
void enterTitleState();
void enterPauseState();
void loadUI();
void loadSprites();
void loadTiles();
Scene* loadSceneInitial(SceneEnum sceneName);

void setGameState(GameStateEnum gStateEnum);

#endif
