#ifndef ARROW_CRIT_ATTACK_H
#define ARROW_CRIT_ATTACK_H

#include "../Attack.h"

class ArrowCritAttack : public Attack {
private:
    int counter;
    int maxCounter;

public:
    ArrowCritAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, int maxCounter);
    ArrowCritAttack(const ArrowCritAttack& other) = default;
    ~ArrowCritAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    void update() override;
    void update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) override;
};

#endif // ARROW_CRIT_ATTACK_H