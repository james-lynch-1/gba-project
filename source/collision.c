
#include "entity.h"
#include <tonc.h>
#include "log.h"

// 4 bits per collision point (max. 16 different tile types)
u32 getPointCollision(Position pos, Scene* scene) {
    CollisionTileRow256x256* sglCollRowPtr = (CollisionTileRow256x256*)scene->sceneData.collisionMap;
    CollisionTileRow512x512* dblCollRowPtr = (CollisionTileRow512x512*)scene->sceneData.collisionMap;
    if (scene->sceneData.mapWInMtiles == 16) {
        return 0 | (sglCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
            ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK);
    }
    else {
        return 0 | (dblCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
            ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK);
    }
}

/** Returns a point along the edge of the hitbox in the given compass direction. */
u32 getEdgePointCollision(Position pos, Hitbox hb, Direction dir, Scene* scene) {
    pos.x.HALF.HI += hb.xOffset + lu_cos(dir) > 0 ? hb.rightOffset : hb.leftOffset;
    pos.y.HALF.HI += hb.yOffset + -lu_sin(dir) > 0 ? hb.bottomOffset : hb.topOffset;
    return getPointCollision(pos, scene);
}

/** Only takes a cardinal direction. Returns collision for three points along a SINGLE side. */
u32 getEdgeCollision(Position pos, Hitbox hb, Direction cardDir, Scene* scene) {
    u32 edgeCollision = 0;
    int yShiftOffset = 12 * (cardDir == NORTH || cardDir == SOUTH);
    Direction pointDir = (cardDir - 0x2000) & 0xFFFF;
    for (int i = 0; i < 3; i++) {
        edgeCollision |= getEdgePointCollision(pos, hb, pointDir, scene)
            << (yShiftOffset + i * COLL_BITWIDTH);
        pointDir = (pointDir + 0x2000) & 0xFFFF;
    }
    return edgeCollision;
}
