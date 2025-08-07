#ifndef REALLY_BIG_BOMBS_ATTACK_H
#define REALLY_BIG_BOMBS_ATTACK_H

#include "../Attack.h"

class ReallyBigBombsAttack : public Attack {
public:
    ReallyBigBombsAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~ReallyBigBombsAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    void update() override; 
    void update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) override;
};

#endif // REALLY_BIG_BOMBS_ATTACK_H