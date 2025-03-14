#include "global.h"

u32 frameCount = 0;

OBJ_ATTR obj_buffer[MAX_ENTS];
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;
Entity* entities;
Scene* scene;
Node* dir_queue;
int numEnts = 0;
int numAttacks = 0;
Direction spinArray[8];

// union SplitWord crosshairX = {.WORD = SCREEN_WIDTH << 16};
// union SplitWord crosshairY = {.WORD = SCREEN_HEIGHT << 16};
// union SplitWord crosshairX = { .WORD = 0 };
// union SplitWord crosshairY = { .WORD = 0 };
Position crosshairPos = {.x.WORD = 8 << 16, .y.WORD = 8 << 16};

int main() {
	initialise();
	entities = loadPlayer();
	scene = loadSceneInitial(Grassland);
	for (int i = 0; i < 8; i++) {
		spinArray[i] = 8;
	}
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
