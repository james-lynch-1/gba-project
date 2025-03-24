#include "global.h"

u32 frameCount = 0;

OBJ_ATTR obj_buffer[MAX_ENTS];
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;
Entity* entities;
Scene* scene;
Viewport vp = {0, 0, 0, 0, 0, 0};
int numEnts = 0;
int numAttacks = 0;
Direction spinArray[8] = {8,8,8,8,8,8,8,8};
Position crosshairPos = {.x.WORD = 8 << 16, .y.WORD = 8 << 16};

int main() {
	initialise();
	entities = loadPlayer();
	scene = loadSceneInitial(Grassland);
	while (1) {
		VBlankIntrWait();
		handleInput();
		updateAttacks();
		handleScroll();
		updateEnts();
		updateCrosshair();

		oam_copy(oam_mem, obj_buffer, MAX_ENTS);
		frameCount++;
	}

	return 0;
}
