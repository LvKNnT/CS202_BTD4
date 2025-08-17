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
    int speed;
    float speedRatio;
    int pierce; 
    float pierceRatio;
    float lifeSpanRatio;
    Vector2 size;

    BulletProperties properties;
    BloonDebuff extraNormalDebuff;
    BloonDebuff extraMoabDebuff;

    AttackBuff(float range = 0.0f, float rangeRatio = 1.0f, float cooldownRatio = 1.0f, int damage = 0, int speed = 0, float speedRatio = 1.0f, int pierce = 0, float pierceRatio = 1.0f, float lifeSpanRatio = 1.0f, Vector2 size = {0.0f, 0.0f}, BulletProperties properties = BulletProperties::classic(), BloonDebuff extraNormalDebuff = BloonDebuff(), BloonDebuff extraMoabDebuff = BloonDebuff())
        : range(range), rangeRatio(rangeRatio), cooldownRatio(cooldownRatio), damage(damage), speed(speed), speedRatio(speedRatio), pierce(pierce), pierceRatio(pierceRatio), lifeSpanRatio(lifeSpanRatio), size(size), properties(properties), extraNormalDebuff(extraNormalDebuff), extraMoabDebuff(extraMoabDebuff) {}
    ~AttackBuff() = default;

    AttackBuff& operator=(const AttackBuff& other) {
        if (this != &other) {
            range = other.range;
            rangeRatio = other.rangeRatio;
            cooldownRatio = other.cooldownRatio;
            damage = other.damage;
            speed = other.speed;
            speedRatio = other.speedRatio;
            pierce = other.pierce;
            pierceRatio = other.pierceRatio;
            lifeSpanRatio = other.lifeSpanRatio;
            size = other.size;
            properties = other.properties;
            extraNormalDebuff = other.extraNormalDebuff;
            extraMoabDebuff = other.extraMoabDebuff;
        }
        return *this;
    }
};

#endif // ATTACKUNITS_H