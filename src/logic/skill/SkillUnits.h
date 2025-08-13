#ifndef SKILL_UNITS_H
#define SKILL_UNITS_H

#include "../tower/Tower.h"
#include "../enemy/Enemy.h"
#include "../bullet/BulletManager.h"

class SkillFriendAccess {
public:
    static Vector2& getTowerPosition(Tower& tower);
    static float& getTowerRotation(Tower& tower);
    static TowerType& getTowerType(Tower& tower);
    static TargetPriority& getTargetPriority(Tower& tower);
    static AttackBuff& getAttackBuff(Tower& tower);
    static std::string& getTag(Tower& tower);
    static int& getTowerId(Tower& tower);

    static Vector2& getEnemyPosition(Enemy& enemy);
    static BloonDebuff& getDebuff(Enemy& enemy);
    static BloonType& getType(Enemy& enemy);
    static int& getLivesLost(Enemy& enemy);
    static int getEnemyId(Enemy& enemy);


    // Enemey
    static BloonType& getEnemyType(Enemy& enemy);
    static int& getEnemyHealth (Enemy& enemy);
    
};

#endif // SKILL_UNITS_H