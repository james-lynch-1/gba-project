#include "attacks.h"

extern Entity* entities;
extern int numAttacks;

// attack functions
// array indices correspond to attack class enums
void (* const beAtkdFns[])(Entity* ent, u8 attackRangeValue) = { beAttackedDirect, beAttackedSpecial };

void (* const atkUpdateFns[])(AttackInstance* atkInst) = { updateAttackDirect, updateAttackSpecial };

void beAttackedDirect(Entity* ent, u8 attackRangeValue) {
    ent->animationState = ANIM_HURT;
    ent->health -= attackRangeValue;
}

void beAttackedSpecial(Entity* ent, u8 attackRangeValue) {
    ent->animationState = ANIM_HURT;
    ent->health -= attackRangeValue;
}

void handlePlayerAttacks(Entity* ent, int crosshairEntColl) {
    ent->animationState = ANIM_IDLE;
    Entity player = *entities;
    AttackInstance* atkInst = player.attacksActive;
    while (atkInst != NULL) {
        if (atkInst->attack->range[crosshairEntColl] != 0 && atkInst->firing && !(atkInst->cooldownTimer))
            beAtkdFns[atkInst->attack->atkClass](ent, atkInst->attack->range[crosshairEntColl]);
        atkInst = atkInst->next;
    }
}

void updateAttackDirect(AttackInstance* atkInst) {
    Attack* atk = atkInst->attack;
    if (atkInst->cooldownTimer) {
        atkInst->cooldownTimer--;
        atkInst->timer = atk->duration + atk->countdown;
        return;
    }
    if (atkInst->timer == 0) {
        atkInst->cooldownTimer = atk->cooldown;
        atkInst->toBeDeleted = 1;
        return;
    }
    if (atkInst->firing) {
        atkInst->timer--;
        return;
    }
    else {
        atkInst->timer = clamp(atkInst->timer + 1, 0, atk->countdown + atk->duration + 1);
        return;
    }
}

void updateAttackSpecial(AttackInstance* atkInst) {
    if (atkInst->timer == 0) {
        atkInst->toBeDeleted = 1;
        return;
    }
    atkInst->timer--;
}

void deleteNextAtkInstance(AttackInstance* atkInst) {
    AttackInstance* toBeDeleted = atkInst->next;
    free(toBeDeleted);
}

AttackInstance* createAttack(Attack* atk) {
    AttackInstance* atkInstPtr = malloc(sizeof(AttackInstance));
    AttackInstance atkInst = {
        .next = NULL,
        .attack = atk,
        .timer = atk->countdown + atk->duration,
        .firing = 1,
        .cooldownTimer = 0,
        .toBeDeleted = 0
    };
    *atkInstPtr = atkInst;
    return atkInstPtr;
}

void pushNewAttack(Attack* atk) {
    if (numAttacks < 4) {
        AttackInstance* atkInstPtr = createAttack(atk);
        AttackInstance* slot = entities->attacksActive;
        while (slot->next != NULL) {
            slot = slot->next;
        }
        slot->next = atkInstPtr;
        numAttacks++;
    }
    else mgbaLog(CHAR VA "too many attacks");
}

// Range array: E, S, W, N, SE, SW, NW, NE, CTR

const Attack basicAtk = {
    .range = {0, 0, 0, 0, 0, 0, 0, 0, 2}, // e.g. does 2 damage/frame to entities in the crosshairs' centre
    .atkClass = DIRECT,
    .anim = 0,
    .countdown = 0,
    .duration = 180,
    .cooldown = 60,
    .id = BASICATK
};

const Attack screenAtk = {
    .range = {2, 2, 2, 2, 2, 2, 2, 2, 2},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 120,
    .duration = 240,
    .cooldown = 600,
    .id = SCREENATK
};

const Attack eastAtk = {
    .range = {2, 0, 0, 0, 0, 0, 0, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = EATK
};

const Attack southAtk = {
    .range = {0, 2, 0, 0, 0, 0, 0, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = SATK
};

const Attack westAtk = {
    .range = {0, 0, 2, 0, 0, 0, 0, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = WATK
};

const Attack northAtk = {
    .range = {0, 0, 0, 2, 0, 0, 0, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = NATK
};

const Attack southeastAtk = {
    .range = {0, 0, 0, 0, 2, 0, 0, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = SEATK
};

const Attack southwestAtk = {
    .range = {0, 0, 0, 0, 0, 2, 0, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = SWATK
};

const Attack northwestAtk = {
    .range = {0, 0, 0, 0, 0, 0, 2, 0, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = NWATK
};

const Attack northeastAtk = {
    .range = {0, 0, 0, 0, 0, 0, 0, 2, 0},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 30,
    .duration = 120,
    .cooldown = 240,
    .id = NEATK
};

const Attack crossAtk = {
    .range = {2, 2, 2, 2, 0, 0, 0, 0, 4},
    .atkClass = SPECIAL,
    .anim = 0,
    .countdown = 0,
    .duration = 512,
    .cooldown = 240,
    .id = CATK
};
