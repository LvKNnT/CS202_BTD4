#ifndef ATTACK_PATTERN_H
#define ATTACK_PATTERN_H

#include "../bullet/BulletManager.h"
#include "AttackUnits.h"

// expected to be a builder pattern in the future

class AttackPattern {
public:
    AttackPattern() = default;
    virtual ~AttackPattern() = default;

    virtual std::unique_ptr<AttackPattern> clone() const = 0; 

    // Pure virtual function to execute the attack pattern
    virtual void execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff& attackBuff, int towerId) = 0;
};

#endif // ATTACK_PATTERN_H