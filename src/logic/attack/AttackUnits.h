#ifndef ATTACKUNITS_H
#define ATTACKUNITS_H

#include "../bullet/BulletUnits.h"
#include "../enemy/EnemyUnits.h"

enum class AttackType {
    NORMAL,
    EXPLOSIVE,
    POISON,
    FIRE,
    ICE
};

class AttackBuff {
public:
    // Attack properties
    float range;
    float rangeRatio;
    float cooldownRatio;
    
    // Bullet properties
    int damage; 
    float speedRatio;
    int pierce; 
    float lifeSpanRatio;
    float pierceRatio = 0.0f;
    bool canStripCamo = false;

    BulletProperties properties;
    BloonDebuff extraNormalDebuff;
    BloonDebuff extraMoabDebuff;

    AttackBuff(float range = 0.0f, float rangeRatio = 1.0f, float cooldownRatio = 1.0f, int damage = 0, float speedRatio = 1.0f, int pierce = 0, float lifeSpanRatio = 1.0f, BulletProperties properties = BulletProperties::classic(), BloonDebuff extraNormalDebuff = BloonDebuff(), BloonDebuff extraMoabDebuff = BloonDebuff())
        : range(range), rangeRatio(rangeRatio), cooldownRatio(cooldownRatio), damage(damage), speedRatio(speedRatio), pierce(pierce), lifeSpanRatio(lifeSpanRatio), properties(properties), extraNormalDebuff(extraNormalDebuff), extraMoabDebuff(extraMoabDebuff) {}
    ~AttackBuff() = default;
};

#endif // ATTACKUNITS_H