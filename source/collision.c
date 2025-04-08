
#include "entity.h"
#include <tonc.h>
#include "log.h"

u32 (* const getPointCollFns[])(Position pos, Scene* scene) = {
    getPointCollision256x256,
    getPointCollision512x512,
    NULL,
    getPointCollision1024x1024
};

u32 getPointCollision256x256(Position pos, Scene* scene) {
    CollisionTileRow256x256* sglCollRowPtr = (CollisionTileRow256x256*)scene->sceneData.collisionMap;
    return (sglCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
        ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK);
}

u32 getPointCollision512x512(Position pos, Scene* scene) {
    CollisionTileRow512x512* dblCollRowPtr = (CollisionTileRow512x512*)scene->sceneData.collisionMap;
    return (dblCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
        ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK);
}

u32 getPointCollision1024x1024(Position pos, Scene* scene) {
    CollisionTileRow1024x1024* quadCollRowPtr = (CollisionTileRow1024x1024*)scene->sceneData.collisionMap;
    return (quadCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
        ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK);
}

/** Returns a point along the edge of the hitbox in the given compass direction. */
u32 getEdgePointCollision(Position pos, Hitbox hb, Direction dir, Scene* scene) {
    pos.x.HALF.HI += hb.xOffset + lu_cos(dir) > 0 ? hb.rightOffset : hb.leftOffset;
    pos.y.HALF.HI += hb.yOffset + -lu_sin(dir) > 0 ? hb.bottomOffset : hb.topOffset;
    return getPointCollFns[scene->sceneData.mapWInMtiles / 16 - 1](pos, scene);
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
