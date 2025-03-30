#include "tile.h"

inline MtTileArray posToMtTiles(Position pos, Scene* scene) {
    u32 tile0 = coordToMtSeIndex(pos, scene);
    MtTileArray tiles = { .t0 = tile0, .t1 = tile0 + 1,
                         .t2 = tile0 + SBB_WIDTH_T, .t3 = tile0 + SBB_WIDTH_T + 1 };
    return tiles;
}

/** Returns the screen entry index of the first tile of the metatile of the supplied position */
u32 coordToMtSeIndex(Position pos, Scene* scene) {
    int metatile = coordToMetatile(pos, scene);
    return metatileToSeIndex(metatile, scene);
}

/** Returns the metatile containing the supplied coordinates. Ignores SBBs */
inline int coordToMetatile(Position pos, Scene* scene) {
    return pos.y.HALF.HI / MT_WIDTH * scene->sceneData.mapWInMtiles + pos.x.HALF.HI / MT_WIDTH;
}

/** Returns the screen entry index of the first tile of the supplied metatile */
u32 metatileToSeIndex(int metatile, Scene* scene) {
    int metaY = metatile / scene->sceneData.mapWInMtiles;
    int metaX = metatile & (scene->sceneData.mapWInMtiles - 1);
    u32 ty = metaY * 2;
    u32 tx = metaX * 2;
    u32 sbb = (ty / SBB_WIDTH_T) * scene->sceneData.mapWInMtiles / SBB_WIDTH_MT +
        tx / SBB_WIDTH_T;
    return sbb * 1024 + (ty & (SBB_WIDTH_T - 1)) * SBB_WIDTH_T + (tx & (SBB_WIDTH_T - 1));
}

u32 coordToSeIndex(Position pos, Scene* scene) {
    u32 ty = pos.y.HALF.HI / TILE_WIDTH;
    u32 tx = pos.x.HALF.HI / TILE_WIDTH;
    u32 sbb = (ty / SBB_WIDTH_T) * scene->sceneData.mapWInMtiles / SBB_WIDTH_MT +
        tx / SBB_WIDTH_T;
    return sbb * 1024 + (ty & (SBB_WIDTH_T - 1)) * SBB_WIDTH_T + (tx & (SBB_WIDTH_T - 1));
}
