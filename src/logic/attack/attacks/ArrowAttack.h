#ifndef ARROW_ATTACK_H
#define ARROW_ATTACK_H

#include "../Attack.h"

class ArrowAttack : public Attack {
public:
    ArrowAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties);
    ArrowAttack(const ArrowAttack& other) = default;
    ~ArrowAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    virtual void update() override;
    void update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) override;
};

#endif // ARROW_ATTACK_H