#ifndef SKILL_UNITS_H
#define SKILL_UNITS_H

#include "../tower/Tower.h"
#include "../enemy/Enemy.h"

class SkillFriendAccess {
public:
    static TowerType& getTowerType(Tower& tower);
    static Vector2& getTowerPosition(Tower& tower);
    static AttackBuff& getAttackBuff(Tower& tower);

    static BloonDebuff& getDebuff(Enemy& enemy);
};

#endif // SKILL_UNITS_H