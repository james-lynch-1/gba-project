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
    u32 sbb = (ty / SBB_WIDTH_T) * scene->sceneData.mapWInMtiles / SBB_WIDTH_MT + tx / SBB_WIDTH_T;
    return sbb * 1024 + (ty & (SBB_WIDTH_T - 1)) * SBB_WIDTH_T + (tx & (SBB_WIDTH_T - 1));
}

TreeNode* generateActionTileTree(const ActionTile* tileArray) { // TODO fix this
    if (!tileArray) return NULL;
    TreeNode* treePtr = malloc(sizeof(TreeNode));
    TreeNode tree = { NULL, NULL, tileArray[0], 0, tileArray[0].data.respawnTime };
    *treePtr = tree;
    int i = 1;
    while (tileArray[i].id != -1) {
        treePtr = insertTreeNode(treePtr, tileArray[i]); // need to do from head
        i++;
    }
    return treePtr;
}

void applyActionTileTreeToCollMap(Scene* scene) {
    if (!scene->actionTileTree) return;
    Node* traversed = createStack(scene->actionTileTree);
    TreeNode* nextNode = getNodeDataAsTreeNode(traversed);
    while (traversed) {
        if (!nextNode) {
            nextNode = getNodeDataAsTreeNode(traversed)->right;
            addActionTileToCollMap(scene, getNodeDataAsTreeNode(traversed));
            traversed = pop(traversed);
            if (!traversed) { // when we reach the top of the tree
                traversed = stackPush(traversed, nextNode);
                nextNode = nextNode->left;
            }
        }
        else {
            nextNode = nextNode->left;
            traversed = stackPush(traversed, nextNode);
        }
    }
}

void addActionTileToCollMap(Scene* scene, TreeNode* actionTileNode) {
    if (!actionTileNode) return;
    ActionTile tile = actionTileNode->tile;
    int tileY = tile.id / scene->sceneData.mapWInMtiles;
    int tileX = tile.id & (scene->sceneData.mapWInMtiles - 1);
    int halfSBBRow = tileX / 8; // which half SBB-sized chunk of the tileRow we are in
    int tileXInHalfSBBRow = tileX - halfSBBRow * 8;
    log(U32, tile.id);
    u32 clearingMask = ~(0xF << (tileXInHalfSBBRow * 4)); // to clear the existing tile
    u32 mask = (tile.data.TileClass << (tileXInHalfSBBRow * 4));
    CollisionTileRow256x256* collMap256Ptr;
    CollisionTileRow512x512* collMap512Ptr;
    CollisionTileRow1024x1024* collMap1024Ptr;

    switch (scene->sceneData.mapWInMtiles) {
        case 16:
            collMap256Ptr = (CollisionTileRow256x256*)scene->sceneData.collisionMap;
            collMap256Ptr[tileY].halfSBBRow[halfSBBRow] &= clearingMask;
            collMap256Ptr[tileY].halfSBBRow[halfSBBRow] |= mask;
            break;
        case 32:
            collMap512Ptr = (CollisionTileRow512x512*)scene->sceneData.collisionMap;
            collMap512Ptr[tileY].halfSBBRow[halfSBBRow] &= clearingMask;
            collMap512Ptr[tileY].halfSBBRow[halfSBBRow] |= mask;
            break;
        case 64:
            collMap1024Ptr = (CollisionTileRow1024x1024*)scene->sceneData.collisionMap;
            collMap1024Ptr[tileY].halfSBBRow[halfSBBRow] &= clearingMask;
            collMap1024Ptr[tileY].halfSBBRow[halfSBBRow] |= mask;
            break;
        default:
            break;
    }
    return;
}

void removeActionTileFromCollMap(Scene* scene, TreeNode* actionTileNode) {
    if (!(scene->actionTileTree)) return;
}
