#ifndef OCTUPLE_ATTACK_H
#define OCTUPLE_ATTACK_H

#include "../AttackPattern.h"

class OctupleAttack : public AttackPattern {
public:
    OctupleAttack() = default;
    ~OctupleAttack() override = default;

    std::unique_ptr<AttackPattern> clone() const override;

    // Override the execute method to implement the triple attack pattern
    void execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float& rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) override;
};

#endif // OCTUPLE_ATTACK_H