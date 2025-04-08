#include "global.h"

u32 frameCount = 0;

OBJ_ATTR obj_buffer[MAX_ENTS];
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;
Entity* entities;
Scene* scene;
Viewport vp = {0, 0, 0, 0, 0, 0};
Direction dPadDir = EAST;
int numEnts = 0;
int numAttacks = 0; // not including basic attack
Position crosshairPos = {.x.WORD = 8 << 16, .y.WORD = 8 << 16};

int main() {
	initialise();
	while (1) {
		VBlankIntrWait();
		handleInput();
		updateAttacks();
		handleScroll();
		updateEnts();
		updateCrosshair();

		oam_copy(oam_mem, obj_buffer, 128);
		frameCount++;
	}

	return 0;
}
