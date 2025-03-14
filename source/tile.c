#include "tile.h"

inline MtTileArray posToMtTiles(Position pos, Scene* scene) {
    u32 tile0 = coordToMtSeIndex(pos, scene);
    MtTileArray tiles = { .t0 = tile0, .t1 = tile0 + 1,
                         .t2 = tile0 + TILES_PER_SBB_ROW, .t3 = tile0 + TILES_PER_SBB_ROW + 1 };
    return tiles;
}

/** Returns the screen entry index of the first tile of the metatile of the supplied position */
u32 coordToMtSeIndex(Position pos, Scene* scene) {
    int metatile = coordToMetatile(pos, scene);
    return metatileToSeIndex(metatile, scene);
}

/** Returns the metatile containing the supplied coordinates. Ignores SBBs */
inline int coordToMetatile(Position pos, Scene* scene) {
    return pos.y.HALF.HI / MT_WIDTH * scene->mapWidthInMetatiles + pos.x.HALF.HI / MT_WIDTH;
}

/** Returns the screen entry index of the first tile of the supplied metatile */
u32 metatileToSeIndex(int metatile, Scene* scene) {
    int metaY = metatile / scene->mapWidthInMetatiles;
    int metaX = metatile % scene->mapWidthInMetatiles;
    u32 ty = metaY * 2;
    u32 tx = metaX * 2;
    u32 sbb = (ty / TILES_PER_SBB_ROW) * scene->mapWidthInMetatiles / MT_PER_SBB_ROW +
        tx / TILES_PER_SBB_ROW;
    return sbb * 1024 + (ty % TILES_PER_SBB_ROW) * TILES_PER_SBB_ROW + (tx % TILES_PER_SBB_ROW);
}

u32 coordToSeIndex(Position pos, Scene* scene) {
    u32 ty = pos.y.HALF.HI / TILE_WIDTH;
    u32 tx = pos.x.HALF.HI / TILE_WIDTH;
    u32 sbb = (ty / TILES_PER_SBB_ROW) * scene->mapWidthInMetatiles / MT_PER_SBB_ROW +
        tx / TILES_PER_SBB_ROW;
    return sbb * 1024 + (ty % TILES_PER_SBB_ROW) * TILES_PER_SBB_ROW + (tx % TILES_PER_SBB_ROW);
}
