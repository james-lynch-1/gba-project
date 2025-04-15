#include "tile.h"

inline MtTileArray posToMtTileArray(Position pos, Scene* scene) {
    return sEIndexToMtTileArraySBB(coordToMtSeIndex(pos, scene));
}

inline MtTileArray sEIndexToMtTileArraySBB(u32 sEIndex) {
    MtTileArray tiles = {
        .t0 = sEIndex,
        .t1 = sEIndex + 1,
        .t2 = sEIndex + SBB_WIDTH_T,
        .t3 = sEIndex + SBB_WIDTH_T + 1
    };
    return tiles;
}

/** gives the four tiles comprising a metatile based on the flat tilemapping in ROM */
inline MtTileArray sEIndexToMtTileArrayFlat(u32 sEIndex, Scene* scene) {
    MtTileArray tiles = {
        .t0 = sEIndex,
        .t1 = sEIndex + 1,
        .t2 = sEIndex + scene->sceneData.mapWInMtiles * 2,
        .t3 = sEIndex + scene->sceneData.mapWInMtiles * 2 + 1
    };
    return tiles;
}

Position mTileToPos(u32 mTile, Scene* scene) {
    u32 metaY = mTile / scene->sceneData.mapWInMtiles;
    u32 metaX = mTile & (scene->sceneData.mapWInMtiles - 1);
    Position pos = { .x = {(metaX * 16) << 16}, .y = {(metaY * 16) << 16} };
    return pos;
}

/** Returns the screen entry index of the first tile of the metatile of the supplied position */
u32 coordToMtSeIndex(Position pos, Scene* scene) {
    int metatile = coordToMtile(pos, scene);
    return mTileToSEIndex(metatile, scene);
}

/** Returns the metatile containing the supplied coordinates. Ignores SBBs */
inline int coordToMtile(Position pos, Scene* scene) {
    return pos.y.HALF.HI / MT_WIDTH * scene->sceneData.mapWInMtiles + pos.x.HALF.HI / MT_WIDTH;
}

/** Returns the screen entry index of the first tile of the supplied metatile */
u32 mTileToSEIndex(u32 mTile, Scene* scene) {
    u32 metaY = mTile / scene->sceneData.mapWInMtiles;
    u32 metaX = mTile & (scene->sceneData.mapWInMtiles - 1);
    u32 ty = metaY * 2, tx = metaX * 2;
    u32 sbb = (ty / SBB_WIDTH_T) * scene->sceneData.mapWInMtiles / SBB_WIDTH_MT +
        tx / SBB_WIDTH_T;
    return sbb * 1024 + (ty & (SBB_WIDTH_T - 1)) * SBB_WIDTH_T + (tx & (SBB_WIDTH_T - 1));
}

/** Returns the screen entry index of the first tile of the supplied metatile. Assumes we are in SBB 0 */
u32 mTileToSEIndexFast(u32 metatile, Scene* scene) {
    int metaY = metatile / scene->sceneData.mapWInMtiles;
    int metaX = metatile & (scene->sceneData.mapWInMtiles - 1);
    u32 ty = metaY * 2, tx = metaX * 2;
    return (ty & (SBB_WIDTH_T - 1)) * SBB_WIDTH_T + (tx & (SBB_WIDTH_T - 1));
}

// ignores SBBs
u32 mTileToSEIndexFlat(u32 metatile, Scene* scene) {
    u32 metaY = metatile / scene->sceneData.mapWInMtiles;
    u32 metaX = metatile & (scene->sceneData.mapWInMtiles - 1);
    u32 ty = metaY * 2, tx = metaX * 2;
    return ty * (scene->sceneData.mapWInMtiles * 2) + tx;
}

MtTileArray mTileToMtTileArrayFlat(u32 metatile, Scene* scene) {
    u32 sEIndex = mTileToSEIndexFlat(metatile, scene);
    return sEIndexToMtTileArrayFlat(sEIndex, scene);
}

u32 coordToSeIndex(Position pos, Scene* scene) {
    u32 ty = pos.y.HALF.HI / TILE_WIDTH;
    u32 tx = pos.x.HALF.HI / TILE_WIDTH;
    u32 sbb = (ty / SBB_WIDTH_T) * scene->sceneData.mapWInMtiles / SBB_WIDTH_MT + tx / SBB_WIDTH_T;
    return sbb * 1024 + (ty & (SBB_WIDTH_T - 1)) * SBB_WIDTH_T + (tx & (SBB_WIDTH_T - 1));
}

TreeNode* generateActionTileTree(const ActionTile* tileArray) {
    if (!tileArray) return NULL;
    TreeNode* treePtr = malloc(sizeof(TreeNode));
    TreeNode tree = { NULL, NULL, tileArray[0], 0, tileArray[0].data.respawnTime };
    *treePtr = tree;
    int i = 1;
    while (tileArray[i].id != -1) {
        treePtr = insertTreeNode(treePtr, tileArray[i]);
        i++;
    }
    return treePtr;
}

void applyActionTileTreeToCollMap(Scene* scene) {
    if (!scene->actionTileTree) return;
    Node* traversed = NULL;
    TreeNode* nextNode = scene->actionTileTree;
    do {
        if (!nextNode) {
            nextNode = getNodeDataAsTreeNode(traversed)->right;
            addActionTileToCollMap(scene, getNodeDataAsTreeNode(traversed));
            traversed = pop(traversed);
            if (!traversed) { // when we reach the top of the tree
                traversed = stackPush(traversed, nextNode);
                if (nextNode) nextNode = nextNode->left;
            }
        }
        else {
            traversed = stackPush(traversed, nextNode);
            nextNode = nextNode->left;
        }
    } while (traversed);
}

void addActionTileToCollMap(Scene* scene, TreeNode* actionTileNode) {
    if (!actionTileNode) return;
    ActionTile tile = actionTileNode->tile;
    int tileY = tile.id / scene->sceneData.mapWInMtiles;
    int tileX = tile.id & (scene->sceneData.mapWInMtiles - 1);
    int halfSBBRow = tileX / 8; // which half SBB-sized chunk of the tileRow we are in
    int tileXInHalfSBBRow = tileX - halfSBBRow * 8;
    u32 clearingMask = ~(0xF << (tileXInHalfSBBRow * 4)); // to clear the existing tile
    u32 mask = (tile.data.tileClass << (tileXInHalfSBBRow * 4));
    CollisionTileRow256x256* collMap256Ptr;
    CollisionTileRow512x512* collMap512Ptr;
    CollisionTileRow1024x1024* collMap1024Ptr;

    switch (scene->sceneData.mapWInMtiles) {
        case 16:
            collMap256Ptr = (CollisionTileRow256x256*)scene->collisionMap;
            collMap256Ptr[tileY].halfSBBRow[halfSBBRow] &= clearingMask;
            collMap256Ptr[tileY].halfSBBRow[halfSBBRow] |= mask;
            break;
        case 32:
            collMap512Ptr = (CollisionTileRow512x512*)scene->collisionMap;
            collMap512Ptr[tileY].halfSBBRow[halfSBBRow] &= clearingMask;
            collMap512Ptr[tileY].halfSBBRow[halfSBBRow] |= mask;
            break;
        case 64:
            collMap1024Ptr = (CollisionTileRow1024x1024*)scene->collisionMap;
            collMap1024Ptr[tileY].halfSBBRow[halfSBBRow] &= clearingMask;
            collMap1024Ptr[tileY].halfSBBRow[halfSBBRow] |= mask;
            break;
        default:
            break;
    }
    return;
}

/** In-order traverses action tile tree and updates each tile */
void updateActionTiles() {
    if (!scene->actionTileTree) return;
    Node* traversed = NULL;
    TreeNode* nextNode = scene->actionTileTree;
    do {
        if (!nextNode) {
            nextNode = getNodeDataAsTreeNode(traversed)->right;
            updateActionTile(getNodeDataAsTreeNode(traversed));
            traversed = pop(traversed);
            if (!traversed) { // when we reach the top of the tree
                traversed = stackPush(traversed, nextNode);
                if (nextNode) nextNode = nextNode->left;
            }
        }
        else {
            traversed = stackPush(traversed, nextNode);
            nextNode = nextNode->left;
        }
    } while (traversed);
}

void updateActionTile(TreeNode* node) {
    if (!node) return;
    // if (node->timer == 0) log(CHAR, "timer == 0");
    // node->timer--;

    // draw check
    Position tilePos = mTileToPos(node->tile.id, scene);
    if (node->timer != 0 && mTileIsWithinViewport(tilePos, vp)) {
        // draw the tile over the spot in the map!!!
        int sEIndex = mTileToSEIndexFast(node->tile.id, scene);
        drawMTile(sEIndex, 502, 13); // TODO: un-hardcode tile mem locations and palettes
    }
}

void drawMTile(u32 sEIndex, u32 tileMemIndex, int pb) {
    MtTileArray vramMtile = sEIndexToMtTileArraySBB(sEIndex);
    se_mem[MAP_SBB][vramMtile.t0] = SE_BUILD(tileMemIndex, pb, 0, 0);
    se_mem[MAP_SBB][vramMtile.t1] = SE_BUILD(tileMemIndex, pb, 1, 0);
    se_mem[MAP_SBB][vramMtile.t2] = SE_BUILD(tileMemIndex, pb, 0, 1);
    se_mem[MAP_SBB][vramMtile.t3] = SE_BUILD(tileMemIndex, pb, 1, 1);
}

void drawMTileFromRom(u32 dstSEIndex, MtTileArray srcMtTileArray) {
    MtTileArray vramMtile = sEIndexToMtTileArraySBB(dstSEIndex);
    se_mem[MAP_SBB][vramMtile.t0] = scene->sceneData.sourceMap[srcMtTileArray.t0];
    se_mem[MAP_SBB][vramMtile.t1] = scene->sceneData.sourceMap[srcMtTileArray.t1];
    se_mem[MAP_SBB][vramMtile.t2] = scene->sceneData.sourceMap[srcMtTileArray.t2];
    se_mem[MAP_SBB][vramMtile.t3] = scene->sceneData.sourceMap[srcMtTileArray.t3];
}
