#ifndef uih
#define uih

#include <tonc.h>
#include "entity.h"
#include "type.h"
#include "constants.h"
#include "global.h"

extern void (* const updateUiFns[])(AttackInstance* atkInst, int atkNum);

void updateQuadCountdownUI(AttackInstance* atkInst, int atkIndex);

void updateBasicAttackUI(AttackInstance* atkInst, int atkIndex);

void updateCrosshair();

#endif
