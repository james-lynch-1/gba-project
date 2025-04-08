#ifndef uih
#define uih

#include "entity.h"
#include "type.h"
#include "constants.h"
#include <tonc.h>

extern void (* const updateUiFns[])(AttackInstance* atkInst, int atkNum);

void updateQuadCountdownUI(AttackInstance* atkInst, int atkIndex);

void updateBasicAttackUI(AttackInstance* atkInst, int atkIndex);

void updateCrosshair();

#endif
