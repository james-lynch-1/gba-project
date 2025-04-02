#include "ui.h"
#include "graphics/graphics.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE* obj_aff_buffer;
extern Entity* entities;
extern Position crosshairPos;
extern int numAttacks;

void updateQuadCountdownUI(int timer, int countdown, int duration, int atkNum) {
    int t = timer;
    int denom = duration;
    if (t > duration) {
        t -= duration;
        denom = countdown;
    }
    t = ((t / 4 << 16) * lu_div(denom / 4)) >> 16; // t = t / denom, in fixed. eg 80/240
    t = (t * (30)) >> 16; // t = (t/denom) / 30 i.e. as a proportion of 30
    // t should now be in the range (0, 30) inclusive.

    // for when the next one runs out and we gotta clear it cos that bar is moving up in the world
    memset32(&se_mem[UI_SBB][(atkNum + 1) * 32], 0, 15);
    // fill a row with bar
    memset16(&se_mem[UI_SBB][atkNum * 32 + 30 - t], 1, t);
    if (timer > duration) { // in countdown
        for (int i = 0; i < 30; i++) se_mem[UI_SBB][atkNum * 32 + i] |= SE_PALBANK(15); // red (duration)
    }
    else { // in duration
        for (int i = 0; i < 30; i++) se_mem[UI_SBB][atkNum * 32 + i] |= SE_PALBANK(14); // yellow (countdown)
    }
    memset16(&se_mem[UI_SBB][atkNum * SBB_WIDTH_T], 0, 30 - t);
}

void updateCrosshair() {
    REG_BG1HOFS = SCR_W + 20 - crosshairPos.x.HALF.HI;
    REG_BG1VOFS = SCR_H + 100 - crosshairPos.y.HALF.HI;
}
