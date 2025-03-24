
#include "entity.h"
#include <tonc.h>
#include "log.h"
#include "stdlib.h"

// 4 bits per collision point (max. 16 different coll types: bouncy, sticky, etc.)
// 8 checks: 4 edges and 4 corners
u32 getTileCollision(Position nextPos, Entity* ent, Scene* scene) {
    Hitbox hitbox = ent->hitbox;
    u32 tileCollision = 0;
    for (Direction dir = 0; dir < 8; dir++)
        tileCollision |= getEdgeCollision(nextPos, hitbox, dir, scene);
    return tileCollision;
}

inline int getTileCollisionPoint(int point[2], Scene* scene) {
    const u16* collMap = scene->sceneData.collisionMap;
    return collMap[(point[1] / MT_WIDTH) * 32 + (point[0] / MT_WIDTH)];
}

u32 getEdgeCollision(Position nextPos, Hitbox hb, Direction dir, Scene* scene) {
    switch (dir) {
    case EAST:
        nextPos.x.HALF.HI += hBoxROffset(hb);
        nextPos.y.HALF.HI += hBoxYOffset(hb);
        break;
    case SOUTH:
        nextPos.x.HALF.HI += hBoxXOffset(hb);
        nextPos.y.HALF.HI += hBoxBOffset(hb);
        break;
    case WEST:
        nextPos.x.HALF.HI += hBoxLOffset(hb);
        nextPos.y.HALF.HI += hBoxYOffset(hb);
        break;
    case NORTH:
        nextPos.x.HALF.HI += hBoxXOffset(hb);
        nextPos.y.HALF.HI += hBoxTOffset(hb);
        break;
    case SOUTHEAST:
        nextPos.x.HALF.HI += hBoxROffset(hb);
        nextPos.y.HALF.HI += hBoxBOffset(hb);
        break;
    case SOUTHWEST:
        nextPos.x.HALF.HI += hBoxLOffset(hb);
        nextPos.y.HALF.HI += hBoxBOffset(hb);
        break;
    case NORTHEAST:
        nextPos.x.HALF.HI += hBoxROffset(hb);
        nextPos.y.HALF.HI += hBoxTOffset(hb);
        break;
    case NORTHWEST:
        nextPos.x.HALF.HI += hBoxLOffset(hb);
        nextPos.y.HALF.HI += hBoxTOffset(hb);
        break;
    default:
        return 0;
    }
    // return 0 | scene->collisionMap[coordToMetatile(nextPos, scene)] << (dir * COLL_BITWIDTH); // old collision maps
    // packed collision maps below:
    CollisionTileRow256x256* sglCollRowPtr = (CollisionTileRow256x256*)scene->sceneData.collisionMap;
    CollisionTileRow512x512* dblCollRowPtr = (CollisionTileRow512x512*)scene->sceneData.collisionMap;
    if (scene->sceneData.mapWInMtiles == 16) {
        return 0 | (sglCollRowPtr[nextPos.y.HALF.HI / MT_WIDTH].halfSBBRow[nextPos.x.HALF.HI / 128] >>
            (nextPos.x.HALF.HI % 128 / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK) <<
            (dir * COLL_BITWIDTH);
    }
    else {
        return 0 | (dblCollRowPtr[nextPos.y.HALF.HI / MT_WIDTH].halfSBBRow[nextPos.x.HALF.HI / 128] >>
            (nextPos.x.HALF.HI % 128 / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK) <<
            (dir * COLL_BITWIDTH);
    }
}
