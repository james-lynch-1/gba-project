#include "ui.h"
#include "graphics/graphics.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE* obj_aff_buffer;
extern Entity* entities;
extern Position crosshairPos;
extern int numAttacks;

void updateQuadCountdownUI(int timer, int countdown, int duration, int atkNum) {
    // for when the next one runs out and we gotta clear it cos that bar is moving up in the world
    memset32(&se_mem[UI_SBB][(atkNum+1)*32], 0, 15);

    int t = timer;
    int denom = duration;
    if (t > duration) {
        t -= duration;
        denom = countdown;
    }
    // set a row to green
    memset16(&se_mem[UI_SBB][atkNum*32], 1, 30);
    if (timer > duration) { // in countdown
        for (int i = 0; i < 30; i++) se_mem[UI_SBB][atkNum*32 + i] |= SE_PALBANK(15); // red (duration)
    }
    if (timer <= duration) { // in duration
        for (int i = 0; i < 30; i++) se_mem[UI_SBB][atkNum*32 + i] |= SE_PALBANK(14); // green (countdown)
    }
    t = fxmul64(int2fx(t), lu_div(denom) >> 8); // t = t / denom, in fixed. eg 80/240
    t = fxmul64(t, 30 << 8); // t = (t/denom) / 32 i.e. as a proportion of 32
    t >>= 8; // un-fixed-ing
    // t should now be in the range (0, 31)
    memset16(&se_mem[UI_SBB][atkNum*32], 0, 30-t);
}

void updateCrosshair() {
    REG_BG1HOFS = SCR_W + 20 - crosshairPos.x.HALF.HI;
    REG_BG1VOFS = SCR_H + 100 - crosshairPos.y.HALF.HI;
}
