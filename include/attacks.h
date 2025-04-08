#ifndef attacksh
#define attacksh

#include <tonc.h>
#include "log.h"
#include "type.h"
#include "constants.h"

extern const Attack basicAtk;
extern const Attack screenAtk;
extern const Attack eastAtk;
extern const Attack southAtk;
extern const Attack westAtk;
extern const Attack northAtk;
extern const Attack southeastAtk;
extern const Attack southwestAtk;
extern const Attack northwestAtk;
extern const Attack northeastAtk;
extern const Attack crossAtk;

extern void (* const beAtkdFns[])(Entity* ent, u8 attackRangeValue);

extern void (* const atkUpdateFns[])(AttackInstance* atkInst);

void deleteNextAtkInstance(AttackInstance* atkInst);
AttackInstance* createAttack(Attack* atk);
void pushNewAttack(Attack* atk);
void handlePlayerAttacks(Entity* ent, int crosshairEntColl);
void updateAttackDirect(AttackInstance* atkInst);
void updateAttackSpecial(AttackInstance* atkInst);
void beAttackedDirect(Entity* ent, u8 attackRangeValue);

void beAttackedSpecial(Entity* ent, u8 attackRangeValue);

#endif
