#ifndef tileh
#define tileh

#include "type.h"
#include "constants.h"
#include "scene.h"

typedef struct MtTileArray_ {
    u16 t0; u16 t1;
    u16 t2; u16 t3;
} MtTileArray;

MtTileArray posToMtTiles(Position pos, Scene* scene);
int coordToMetatile(Position pos, Scene* scene);
u32 coordToMtSeIndex(Position pos, Scene* scene);
u32 metatileToSeIndex(int metatile, Scene* scene);
u32 coordToSeIndex(Position pos, Scene* scene);

#endif
