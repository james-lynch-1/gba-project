#include "main.h"
#include "global.h"

int main() {
    initialise();
    while (1) {
        gameState.updateFunction();
        frameCount++;
    }
    return 0;
}

void updateGameNormal() {
    handleInput();
    VBlankIntrWait();
    updateAttacks();
    handleScroll();
    updateEnts();
    updateActionTiles();
    updateCrosshair();
    oam_copy(oam_mem, obj_buffer, 128);
}

void updateGameTitle() {
    handleInputTitle();
    VBlankIntrWait();
    updateAttacks();
    handleScroll();
    updateEnts();
    updateActionTiles();
    updateCrosshair();
    oam_copy(oam_mem, obj_buffer, 128);
}

void updateGamePause() {
    handleInputPause();
    VBlankIntrWait();
    
    oam_copy(oam_mem, obj_buffer, 128);
}

void doNothing() {
    log(CHAR, "doing nothing");
}
