#ifndef CALTROPSATTACK_H
#define CALTROPSATTACK_H

#include "../Attack.h"

class CaltropsAttack : public Attack {
public:
    CaltropsAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~CaltropsAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    void update() override; 
    void update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) override;
};

#endif // CALTROPSATTACK_H