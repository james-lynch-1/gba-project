#include "ui.h"
#include "graphics/graphics.h"

extern OBJ_ATTR obj_buffer[128];
extern OBJ_AFFINE* obj_aff_buffer;
extern Entity* entities;
extern Position crosshairPos;
extern int numAttacks;

void (* const updateUiFns[])(AttackInstance* atkInst, int atkNum) = {
    updateBasicAttackUI, updateQuadCountdownUI
};

void updateQuadCountdownUI(AttackInstance* atkInst, int atkIndex) {
    Attack* atk = atkInst->attack;
    int atkNum = atkIndex - 1;
    int t = atkInst->timer;
    int denom = atk->duration;
    if (t > atk->duration) {
        t -= atk->duration;
        denom = atk->countdown;
    }
    t = ((t / 4 << 16) * lu_div(denom / 4)) >> 16; // t = t / denom, in fixed. eg 80/240
    t = (t * (30)) >> 16; // t = (t/denom) / 30 i.e. as a proportion of 30
    // t should now be in the range (0, 30) inclusive.

    // for when the next one runs out and we gotta clear it cos that bar is moving up in the world
    memset32(&se_mem[UI_SBB][(atkNum + 1) * 32], 0, 15);
    // fill a row with bar
    memset16(&se_mem[UI_SBB][atkNum * 32 + 30 - t], 1, t);
    if (atkInst->timer > atk->duration) { // in countdown
        for (int i = 0; i < 30; i++) se_mem[UI_SBB][atkNum * 32 + i] |= SE_PALBANK(15); // red (duration)
    }
    else { // in duration
        for (int i = 0; i < 30; i++) se_mem[UI_SBB][atkNum * 32 + i] |= SE_PALBANK(14); // yellow (countdown)
    }
    memset16(&se_mem[UI_SBB][atkNum * SBB_WIDTH_T], 0, 30 - t);
}

void updateBasicAttackUI(AttackInstance* atkInst, int atkIndex) {
    Attack* atk = atkInst->attack;
    int t, denom;
    switch ((atkInst->cooldownTimer != 0) + 2 * (atkInst->timer < atk->duration)) {
        case 2: // duration
            t = atkInst->timer;
            denom = atk->duration;
            break;
        case 1:
        case 3: // cooldown
            t = atk->cooldown - atkInst->cooldownTimer;
            denom = atk->cooldown;
            break;
        case 0:
        default: // countdown
            t = atkInst->timer - atk->duration + 1;
            denom = atk->countdown;
            break;
    }
    t = ((t << 16) * lu_div(denom)) >> 16; // t = t / denom, in fixed. eg 80/240
    t = (t * (basicCountdownTilesLen / 32)) >> 16; // t = (t/denom) / 12 i.e. as a proportion of 12
    // t should now be in the range (0, 12) inclusive.
    obj_set_attr(&obj_buffer[0],
        (ATTR0_Y(crosshairPos.y.HALF.HI) - 4) | ATTR0_REG | ATTR0_4BPP | ATTR0_SQUARE,
        (ATTR1_X(crosshairPos.x.HALF.HI) - 4) | ATTR1_SIZE_8,
        ATTR2_ID(80 + t) | ATTR2_PRIO(0) | ATTR2_PALBANK(15));
    return;
}

void updateCrosshair() {
    REG_BG1HOFS = SCR_W + 20 - crosshairPos.x.HALF.HI;
    REG_BG1VOFS = SCR_H + 100 - crosshairPos.y.HALF.HI;
}
