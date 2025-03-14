#include "initialise.h"
#include "scene.h"
#include "entity.h"
#include "graphics/graphics.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE* obj_aff_buffer;
extern u16 numEnts;

void initialise() {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    oam_init(obj_buffer, MAX_ENTS);
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_OBJ | DCNT_OBJ_1D;
    REG_BG0CNT = BG_PRIO(3) | BG_CBB(0) | BG_SBB(28) | BG_4BPP | BG_REG_64x64; // map
    REG_BG1CNT = BG_PRIO(2) | BG_CBB(3) | BG_SBB(27) | BG_4BPP | BG_REG_32x32; // crosshairs
    REG_BG2CNT = BG_PRIO(1) | BG_CBB(2) | BG_SBB(26) | BG_4BPP | BG_REG_32x32; // bars/ui
    loadSprites();
    loadCrosshairs();
}


void loadCrosshairs() {
    // Load palette
    memcpy32(&pal_bg_bank[15], crosshairsPal, crosshairsPalLen / sizeof(u32));
    // // Load tiles into CBB 3
    memcpy32(&tile_mem[3][0], crosshairsTiles, crosshairsTilesLen / sizeof(u32));
    // // Load map into SBB 27
    memcpy32(&se_mem[CHAIR_SBB][0], crosshairsMap, crosshairsMapLen / sizeof(u32));

    // Make crosshairs use the last palbank
    for (int i = 0; i < 32; i++) se_mem[CHAIR_SBB][i] |= SE_PALBANK(15);
    for (int i = 32; i < 1024; i += 32) se_mem[CHAIR_SBB][i] |= SE_PALBANK(15);

    // bg2 countdown bar
    memcpy32(&pal_bg_bank[14], countdownPal, countdownPalLen / sizeof(u32));
    memcpy32(&tile_mem[2][0], countdownTiles, countdownTilesLen / sizeof(u32));
}

void loadSprites() {
    memcpy32(&tile_mem[4][0], squinky1Tiles, squinky1TilesLen / sizeof(u32));
    memcpy32(&tile_mem[4][16], squinky2Tiles, squinky2TilesLen / sizeof(u32));
    memcpy32(&tile_mem[4][32], squinky4Tiles, squinky4TilesLen / sizeof(u32));
    memcpy32(pal_obj_bank[0], squinky1Pal, squinkyPalLen / sizeof(u32));
    memcpy32(&tile_mem[4][48], debugBlobTiles, debugBlobTilesLen / sizeof(u32));
    memcpy32(&pal_obj_bank[1], debugBlobPal, debugBlobPalLen / sizeof(u32));
}

Scene* loadSceneInitial(SceneEnum sceneName) {
    Scene* scene = malloc(sizeof(Scene));
    loadScene(scene, sceneName);
    return scene;
}
