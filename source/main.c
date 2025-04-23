#include "main.h"

int main() {
	initialise();
	while (1) {
		updateGameFns[state]();
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
    frameCount++;
}

void updateGameTitle() {
    VBlankIntrWait();
	handleInputTitle();
}

void (* const updateGameFns[])() = {
    updateGameNormal,
    updateGameTitle
};
