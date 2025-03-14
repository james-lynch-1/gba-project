#include "type.h"
#include "scene.h"
#include "graphics/graphics.h"

extern Entity* entities;
extern Scene* scene;
extern u16 numEnts;

void loadScene(Scene* scene, SceneEnum sceneName) {
    Entity* ent = entities->next;
    while (ent != NULL) {
        ent->toBeDeleted = true;
        ent = ent->next;
    }
    scene->sceneId = sceneName;
    scene->tid = 0;
    scene->pb = 0;
    scene->numEnts = numEnts;
    Position pos = {.x.HALF.HI = 120, .y.HALF.HI = 120};
    Position pos2 = {.x.HALF.HI = 58, .y.HALF.HI = 200};
    Position pos3 = {.x.HALF.HI = 130, .y.HALF.HI = 150};
    switch (sceneName) {
    case Brin:
        loadBG
        (
            brinPal, brinPalLen, 
            brinTiles, brinTilesLen, 
            brinMap, brinMapLen
        );
        spawnFella(pos);
        spawnFella(pos2);
        spawnFella(pos3);
        scene->collisionMap = brinColl;
        scene->mapWidthInMetatiles = 32;
        scene->mapHeightInMetatiles = 32;
        break;
    case Grassland:
        loadBG
        (
            grasslandPal, grasslandPalLen,
            grasslandTiles, grasslandTilesLen,
            grasslandMap, grasslandMapLen
        );
        spawnFella(pos);
        spawnFella(pos2);
        spawnFella(pos3);
        scene->collisionMap = grassColl;
        scene->mapWidthInMetatiles = 32;
        scene->mapHeightInMetatiles = 32;
        break;
    case Home:
        loadBG
        (
            homePal, homePalLen,
            homeTiles, homeTilesLen,
            homeMap, homeMapLen
        );
        spawnFella(pos);
        spawnFella(pos2);
        spawnFella(pos3);
        scene->collisionMap = homeColl;
        scene->mapWidthInMetatiles = 16;
        scene->mapHeightInMetatiles = 16;
        break;
    }
    return;
}

void loadPreviousScene(Scene* currScene) {
    int id = currScene->sceneId - 1;
    if (id < 0) id = NUM_SCENES - 1;
    loadScene(currScene, id);
}

void loadNextScene(Scene* currScene) {
    int id = currScene->sceneId + 1;
    if (id >= NUM_SCENES) id = 0;
    loadScene(currScene, id);
}

void loadBG(const u16* pal, int palLen, const u16* tiles, int tilesLen, const u16* map, int mapLen) {
	// Load palette
	memcpy16(pal_bg_mem, pal, palLen / sizeof(u16));
	// // Load tiles into CBB 0
	memcpy32(&tile_mem[0][0], tiles, tilesLen / sizeof(u32));
	// // Load map into SBB 28
	memcpy32(&se_mem[MAP_SBB][0], map, mapLen / sizeof(u32));
}
