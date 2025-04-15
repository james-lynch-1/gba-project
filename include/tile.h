#ifndef tileh
#define tileh

#include "type.h"
#include "log.h"
#include "constants.h"
#include "scene.h"
#include "avl.h"
#include "graphics/graphics.h"

extern Scene* scene;
extern Viewport vp;

typedef struct MtTileArray_ {
    u16 t0; u16 t1;
    u16 t2; u16 t3;
} MtTileArray;

enum tileClass {
    T_EMPTY = 0,
    T_FILLED = 1,
    T_NW_FILLED = 2,
    T_NE_FILLED = 3,
    T_SW_FILLED = 4,
    T_SE_FILLED = 5,
    T_3_8_E_FILLED = 6,
    T_3_8_W_FILLED = 7,
    T_3_8_S_FILLED = 8, // 3/8ths filled, on the south side
    T_3_8_N_FILLED = 9,
    T_ACTION = 15
};

MtTileArray posToMtTileArray(Position pos, Scene* scene);
MtTileArray sEIndexToMtTileArraySBB(u32 sEIndex);
MtTileArray sEIndexToMtTileArrayFlat(u32 sEIndex, Scene* scene);
Position mTileToPos(u32 mTile, Scene* scene);
int coordToMtile(Position pos, Scene* scene);
u32 mTileToSEIndex(u32 mTile, Scene* scene);
u32 coordToMtSeIndex(Position pos, Scene* scene);
u32 mTileToSEIndexFast(u32 metatile, Scene* scene);
u32 mTileToSEIndexFlat(u32 metatile, Scene* scene);
MtTileArray mTileToMtTileArrayFlat(u32 metatile, Scene* scene);
u32 coordToSeIndex(Position pos, Scene* scene);

TreeNode* generateActionTileTree(const ActionTile* tileArray);
void applyActionTileTreeToCollMap(Scene* scene);
void addActionTileToCollMap(Scene* scene, TreeNode* actionTileNode);

void updateActionTiles();

void updateActionTile(TreeNode* node);

void drawMTile(u32 sEIndex, u32 tileMemIndex, int pb);

void drawMTileFromRom(u32 dstSEIndex, MtTileArray srcMtTileArray);

#endif
