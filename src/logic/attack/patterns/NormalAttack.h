#ifndef NORMAL_ATTACK_H
#define NORMAL_ATTACK_H

#include "../AttackPattern.h"

class NormalAttack : public AttackPattern {
public:
    NormalAttack() = default;
    ~NormalAttack() override = default;

    std::unique_ptr<AttackPattern> clone() const override;

    // Override the execute method to implement the normal attack pattern
    void execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) override;
};

#endif // NORMAL_ATTACK_H