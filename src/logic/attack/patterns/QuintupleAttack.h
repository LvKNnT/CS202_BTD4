#ifndef QUINTUPLE_ATTACK_H
#define QUINTUPLE_ATTACK_H

#include "../AttackPattern.h"

class QuintupleAttack : public AttackPattern {
public:
    QuintupleAttack() = default;
    ~QuintupleAttack() override = default;

    std::unique_ptr<AttackPattern> clone() const override;

    // Override the execute method to implement the triple attack pattern
    void execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) override;
};

#endif // QUINTUPLE_ATTACK_H