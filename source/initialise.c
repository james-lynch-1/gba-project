#include "initialise.h"

void initialise() {
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    oam_init(obj_buffer, MAX_ENTS);
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_OBJ | DCNT_OBJ_1D;
    REG_BG0CNT = BG_PRIO(3) | BG_CBB(0) | BG_SBB(MAP_SBB) | BG_4BPP | BG_REG_32x32; // map
    REG_BG1CNT = BG_PRIO(2) | BG_CBB(3) | BG_SBB(CHAIR_SBB) | BG_4BPP | BG_REG_32x32; // crosshairs
    REG_BG2CNT = BG_PRIO(1) | BG_CBB(2) | BG_SBB(UI_SBB) | BG_4BPP | BG_REG_32x32; // bars/ui
    entities = loadPlayer();
    entities->attacksActive = createAttack(&basicAtk);
    scene = loadSceneInitial(Grassland);
    loadSprites();
    loadUI();
    loadTiles();
}


void loadUI() {
    // BG3 crosshairs
    memcpy32(&tile_mem[3][0], crosshairsTiles, crosshairsTilesLen / sizeof(u32));
    // BG2 countdown bar
    memcpy32(&tile_mem[2][0], countdownTiles, countdownTilesLen / sizeof(u32));
    // basic atk sprite
    memcpy32(&tile_mem[4][80], basicCountdownTiles, basicCountdownTilesLen / sizeof(u32));

    // Load map into SBB 27
    memcpy32(&se_mem[CHAIR_SBB][0], crosshairsMap, crosshairsMapLen / sizeof(u32));

    // Load palette
    memcpy32(pal_bg_bank[15], crosshairsPal, crosshairsPalLen / sizeof(u32));
    memcpy32(pal_bg_bank[14], countdownPal, countdownPalLen / sizeof(u32));
    memcpy32(pal_obj_bank[15], basicCountdownPal, basicCountdownPalLen / sizeof(u32));

    // Make crosshairs use the last palbank
    for (int i = 0; i < 32; i++) se_mem[CHAIR_SBB][i] |= SE_PALBANK(15);
    for (int i = 32; i < 1024; i += 32) se_mem[CHAIR_SBB][i] |= SE_PALBANK(15);
}

void loadSprites() {
    memcpy32(&tile_mem[4][0], squinky1Tiles, squinky1TilesLen / sizeof(u32));
    memcpy32(&tile_mem[4][16], squinky2Tiles, squinky2TilesLen / sizeof(u32));
    memcpy32(&tile_mem[4][32], squinky3Tiles, squinky3TilesLen / sizeof(u32));
    memcpy32(&tile_mem[4][48], squinky4Tiles, squinky4TilesLen / sizeof(u32));
    memcpy32(&tile_mem[4][64], debugBlobTiles, debugBlobTilesLen / sizeof(u32));

    memcpy32(pal_obj_bank[0], squinky1Pal, squinkyPalLen / sizeof(u32));
    memcpy32(&pal_obj_bank[1], debugBlobPal, debugBlobPalLen / sizeof(u32));
}

// commonly used bg tiles such as item pickups
void loadTiles() {
    memcpy32(&tile_mem[0][500], atkIconsTiles, atkIconsTilesLen / sizeof(u32));
    memcpy32(pal_bg_bank[13], atkIconsPal, atkIconsPalLen / sizeof(u32));
}

Scene* loadSceneInitial(SceneEnum sceneName) {
    Scene* scene = malloc(sizeof(Scene));
    loadScene(scene, sceneName);
    return scene;
}
