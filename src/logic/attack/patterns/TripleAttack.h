#ifndef TRIPLE_ATTACK_H
#define TRIPLE_ATTACK_H

#include "../AttackPattern.h"

class TripleAttack : public AttackPattern {
public:
    TripleAttack() = default;
    ~TripleAttack() override = default;

    std::unique_ptr<AttackPattern> clone() const override;

    // Override the execute method to implement the triple attack pattern
    void execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff& attackBuff, int towerId) override;
};

#endif // TRIPLE_ATTACK_H