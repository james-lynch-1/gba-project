
#include "type.h"
#include "tile.h"
#include "log.h"
#include "graphics/maps/grassland.h"
#include "attacks.h"
#include "entity.h"

extern Entity* entities;
extern Scene* scene;

TileCollArray TileCollArrays[16] = {
    {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, // empty
    {
        {0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u}
    }, // filled
    {
        {0b1111111111111111u,
         0b0111111111111111u,
         0b0011111111111111u,
         0b0001111111111111u,
         0b0000111111111111u,
         0b0000011111111111u,
         0b0000001111111111u,
         0b0000000111111111u,
         0b0000000011111111u,
         0b0000000001111111u,
         0b0000000000111111u,
         0b0000000000011111u,
         0b0000000000001111u,
         0b0000000000000111u,
         0b0000000000000011u,
         0b0000000000000001u}
    }, // NW filled
    {
        {0b1111111111111111u,
         0b1111111111111110u,
         0b1111111111111100u,
         0b1111111111111000u,
         0b1111111111110000u,
         0b1111111111100000u,
         0b1111111111000000u,
         0b1111111110000000u,
         0b1111111100000000u,
         0b1111111000000000u,
         0b1111110000000000u,
         0b1111100000000000u,
         0b1111000000000000u,
         0b1110000000000000u,
         0b1100000000000000u,
         0b1000000000000000u}
    }, // NE filled
    {
        {0b0000000000000001u,
         0b0000000000000011u,
         0b0000000000000111u,
         0b0000000000001111u,
         0b0000000000011111u,
         0b0000000000111111u,
         0b0000000001111111u,
         0b0000000011111111u,
         0b0000000111111111u,
         0b0000001111111111u,
         0b0000011111111111u,
         0b0000111111111111u,
         0b0001111111111111u,
         0b0011111111111111u,
         0b0111111111111111u,
         0b1111111111111111u}
    }, // SW filled
    {
        {0b1000000000000000u,
         0b1100000000000000u,
         0b1110000000000000u,
         0b1111000000000000u,
         0b1111100000000000u,
         0b1111110000000000u,
         0b1111111000000000u,
         0b1111111100000000u,
         0b1111111110000000u,
         0b1111111111000000u,
         0b1111111111100000u,
         0b1111111111110000u,
         0b1111111111111000u,
         0b1111111111111100u,
         0b1111111111111110u,
         0b1111111111111111u}
    }, // SE filled
    {
        {0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u,
         0b1111110000000000u}
    }, // 3/8 E filled
    {
        {0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u,
         0b0000000000111111u}
    }, // 3/8 W filled
    {
        {0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u}
    }, // 3/8 S filled
    {
        {0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b1111111111111111u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u,
         0b0000000000000000u}
    }, // 3/8 N filled
    {},
    {},
    {},
    {},
    {},
    {},
};

u32(* const handlePointCollFns[])(Position pos, u32 tileColl) = {
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    getInTilePointColl,
    handleItemTileColl,
    handleActionTileColl
};

u32 getInTilePointColl(Position pos, u32 tileColl) {
    return (TileCollArrays[tileColl].row[pos.y.HALF.HI & 15] & (1 << (pos.x.HALF.HI & 15))) != 0;
}

u32 handleItemTileColl(Position pos, u32 tileColl) {
    TreeNode* node = findTreeNode(scene->actionTileTree, coordToMtile(pos, scene));
    u32 seIndex = mTileToSEIndexFast(node->tile.id, scene);
    MtTileArray srcMtTileArray = mTileToMtTileArrayFlat(node->tile.id, scene);
    pushNewAttack(atks[node->tile.data.action]);
    void* collMap = (void*)scene->sceneData.sourceCollisionMap;
    int originalCollision = getPointCollFns[scene->sceneData.mapWInMtiles / 16 - 1](pos, collMap);
    TreeNode restoreNode = { NULL, NULL, {node->tile.id, {0, originalCollision, 0}} };
    drawMTileFromRom(seIndex, srcMtTileArray); // restore original tile
    addActionTileToCollMap(scene, &restoreNode); // restore original collision
    scene->actionTileTree = deleteTreeNode(scene->actionTileTree, node->tile.id);
    return 0;
}

int doAction(int actionTileId) {
    // TreeNode* node = findTreeNode(scene->actionTileTree, actionTileId);
    // if (!node) return 0;
    // ActionTile* tile = &node->tile;
    return 0;
}

u32 handleActionTileColl(Position pos, u32 tileColl) {
    int mTile = coordToMtile(pos, scene);
    return doAction(mTile);
}

u32(* const getPointCollFns[])(Position pos, void* collisionMap) = {
    getPointCollision256x256,
    getPointCollision512x512,
    NULL,
    getPointCollision1024x1024
};

u32 getPointCollision256x256(Position pos, void* collisionMap) {
    CollisionTileRow256x256* sglCollRowPtr = (CollisionTileRow256x256*)collisionMap;
    u32 tileColl = sglCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
        ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK;
    return handlePointCollFns[tileColl](pos, tileColl);
}

u32 getPointCollision512x512(Position pos, void* collisionMap) {
    CollisionTileRow512x512* dblCollRowPtr = (CollisionTileRow512x512*)collisionMap;
    u32 tileColl = dblCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
        ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK;
    return handlePointCollFns[tileColl](pos, tileColl);
}

u32 getPointCollision1024x1024(Position pos, void* collisionMap) {
    CollisionTileRow1024x1024* quadCollRowPtr = (CollisionTileRow1024x1024*)collisionMap;
    u32 tileColl = quadCollRowPtr[pos.y.HALF.HI / MT_WIDTH].halfSBBRow[pos.x.HALF.HI / 128] >>
        ((pos.x.HALF.HI & 127) / 16 * COLL_BITWIDTH) & PACKED_COLLMAP_MASK;
    return handlePointCollFns[tileColl](pos, tileColl);
}

/** Returns a point along the edge of the hitbox in the given compass direction. */
u32 getEdgePointCollision(Position pos, Hitbox hb, Direction dir, Scene* scene) {
    pos.x.HALF.HI += hb.xOffset + lu_cos(dir) > 0 ? hb.rightOffset : hb.leftOffset;
    pos.y.HALF.HI += hb.yOffset + -lu_sin(dir) > 0 ? hb.bottomOffset : hb.topOffset;
    return getPointCollFns[scene->sceneData.mapWInMtiles / 16 - 1](pos, scene->collisionMap);
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
