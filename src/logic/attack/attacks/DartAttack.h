#ifndef DARTATTACK_H
#define DARTATTACK_H

#include "../Attack.h"

class DartAttack : public Attack {
public:
    DartAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties);
    ~DartAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    void update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) override;
};

#endif // DARTATTACK_H