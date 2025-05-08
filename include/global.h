#ifndef globalh
#define globalh

#include "tonc.h"
#include "type.h"

extern u32 frameCount;

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE* obj_aff_buffer;

extern GameState gameState;
extern Entity* entities;
extern Scene* scene;
extern Viewport vp;
extern Direction dPadDir;
extern int numEnts;
extern int numAttacks; // not including basic attack
extern Position crosshairPos;

extern void updateGameNormal();
extern void updateGameTitle();
extern void updateGamePause();
extern void doNothing();

#endif
