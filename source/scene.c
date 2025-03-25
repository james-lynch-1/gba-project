#include "type.h"
#include "scene.h"
#include "graphics/graphics.h"

extern Entity* entities;
extern Scene* scene;
extern u16 numEnts;
extern Viewport vp;

const struct SceneData sceneDataArr[NUM_SCENES] = { {
    .sceneId = Grassland,
    .sourceMap = grasslandMap,
    .collisionMap = grasslandColl,
    .mapWInMtiles = 32,
    .mapHInMTiles = 32
}, {
    .sceneId = Home,
    .sourceMap = homeMap,
    .collisionMap = homeColl,
    .mapWInMtiles = 16,
    .mapHInMTiles = 16
}, {
    .sceneId = Uglybig,
    .sourceMap = uglybigMap,
    .collisionMap = uglybigColl,
    .mapWInMtiles = 64,
    .mapHInMTiles = 64
} };

void loadScene(Scene* scene, SceneEnum sceneName) {
    scene->sceneData = sceneDataArr[sceneName];

    vp.xMax = scene->sceneData.mapWInMtiles * 16 - SCR_W;
    vp.yMax = scene->sceneData.mapHInMTiles * 16 - SCR_H;
    moveViewportOnMap(entities, scene);
    scene->screenX = vp.x;
    scene->screenY = vp.y;
    updateBGTiles(scene);

    Entity* ent = entities->next;
    while (ent != NULL) {
        ent->toBeDeleted = true;
        ent = ent->next;
    }
    scene->numEnts = numEnts;

    scene->tid = 0;
    scene->pb = 0;

    Position pos = { .x.HALF.HI = 120, .y.HALF.HI = 120 };
    Position pos2 = { .x.HALF.HI = 58, .y.HALF.HI = 200 };
    Position pos3 = { .x.HALF.HI = 130, .y.HALF.HI = 150 };
    switch (sceneName) {
        case Grassland:
            spawnFella(pos);
            spawnFella(pos2);
            spawnFella(pos3);
            loadBG(
                grasslandPal, grasslandPalLen,
                grasslandTiles, grasslandTilesLen,
                grasslandMap, grasslandMapLen,
                scene
            );
            break;
        case Home:
            spawnFella(pos);
            spawnFella(pos2);
            spawnFella(pos3);
            loadBG(
                homePal, homePalLen,
                homeTiles, homeTilesLen,
                homeMap, homeMapLen,
                scene
            );
            break;
        case Uglybig:
            loadBG(
                uglybigPal, uglybigPalLen,
                uglybigTiles, uglybigTilesLen,
                uglybigMap, uglybigMapLen,
                scene
            );
            break;
    }
    return;
}

void loadBG(const u16* pal, int palLen, const u16* tiles, int tilesLen, const u16* map, int mapLen,
    Scene* scene) {
    memcpy16(pal_bg_mem, pal, palLen / sizeof(u16));
    memcpy32(&tile_mem[0][0], tiles, tilesLen / sizeof(u32));
    int srcWInTiles = scene->sceneData.mapWInMtiles * 2;
    int tX = vp.x / 8, tY = vp.y / 8;
    int tXMod = tX & 31, tYMod = tY & 31;
    int srcRow = tY;
    for (int dstRow = tYMod; dstRow < 32; dstRow++) { // from tY to the end of the SBB
        memcpy16(&se_mem[MAP_SBB][dstRow * SBB_WIDTH_T + tXMod], &map[srcRow * srcWInTiles + tX], 32 - tXMod);
        memcpy16(&se_mem[MAP_SBB][dstRow * SBB_WIDTH_T], &map[srcRow++ * srcWInTiles + tX + 32 - tXMod], tXMod);
    }
    for (int dstRow = 0; dstRow < tYMod; dstRow++) { // from the start of the SBB to tY
        memcpy16(&se_mem[MAP_SBB][dstRow * SBB_WIDTH_T + tXMod], &map[srcRow * srcWInTiles + tX], 32 - tXMod);
        memcpy16(&se_mem[MAP_SBB][dstRow * SBB_WIDTH_T], &map[srcRow++ * srcWInTiles + tX + 32 - tXMod], tXMod);
    }
}

void copyTileCol(Scene* scene, int tileX, int tileY) {
    int tXMod = tileX & 31;
    int tYMod = tileY & 31;
    int srcWInTiles = scene->sceneData.mapWInMtiles * 2;

    SCR_ENTRY* srcStartTile = (u16*)&scene->sceneData.sourceMap[tileY * srcWInTiles + tileX];
    SCR_ENTRY* dstStartTile = (u16*)&se_mem[MAP_SBB][tYMod * 32 + tXMod];

    for (int i = tYMod; i < 32; i++) {
        *dstStartTile = *srcStartTile;
        dstStartTile += 32;
        srcStartTile += srcWInTiles;
    }

    dstStartTile -= SBB_SIZE / sizeof(SCR_ENTRY);

    for (int i = 0; i < tYMod; i++) {
        *dstStartTile = *srcStartTile;
        dstStartTile += 32;
        srcStartTile += srcWInTiles;
    }
}

void copyTileRow(Scene* scene, int tileX, int tileY) {
    int tXMod = tileX & 31;
    int tYMod = tileY & 31;
    int srcWInTiles = scene->sceneData.mapWInMtiles * 2;

    SCR_ENTRY* srcStartTile = (u16*)&scene->sceneData.sourceMap[tileY * srcWInTiles + tileX];
    SCR_ENTRY* dstStartTile = (u16*)&se_mem[MAP_SBB][tYMod * 32 + tXMod];

    for (int i = tXMod; i < 32; i++)
        *dstStartTile++ = *srcStartTile++;

    dstStartTile -= SBB_HEIGHT_T;

    for (int i = 0; i < tXMod; i++)
        *dstStartTile++ = *srcStartTile++;
}
