// for global variables and data
#include "global.h"

u32 frameCount = 0;

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE* obj_aff_buffer = (OBJ_AFFINE*)obj_buffer;

int state = NORMAL;
Entity* entities;
Scene* scene = NULL;
Viewport vp = { 0, 0, 0, 0, 0, 0 };
Direction dPadDir = STATIONARY;
int numEnts = 0;
int numAttacks = 0; // not including basic attack
Position crosshairPos = { .x.WORD = 8 << 16, .y.WORD = 8 << 16 };
