#ifndef sceneh
#define sceneh

#include "log.h"

#define NUM_SCENES 3
typedef enum SceneEnum_ {
    Brin = 0,
    Grassland = 1,
    Home = 2,
} SceneEnum;

typedef struct Scene_ {
    SceneEnum sceneId;
    void* collisionMap;
    u16 screenX;
    u16 screenY;
    u8 numEnts;
    u8 mapWidthInMetatiles;
    u8 mapHeightInMetatiles;
    u16 tid : 9;
    u16 pb : 4;
} Scene;

void loadScene(Scene* currScene, SceneEnum sceneName);

void loadBG(const u16* pal, int palLen, const u16* tiles, int tilesLen, const u16* map, int mapLen);

void loadPreviousScene(Scene* currScene);

void loadNextScene(Scene* currScene);

#endif
