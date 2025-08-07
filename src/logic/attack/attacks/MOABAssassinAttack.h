#ifndef MOAB_ASSASSIN_ATTACK_H
#define MOAB_ASSASSIN_ATTACK_H

#include "../Attack.h"

class MOABAssassinAttack : public Attack {
public:
    MOABAssassinAttack(Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~MOABAssassinAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    void update() override; 
    void update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) override;
};

#endif // MOAB_ASSASSIN_ATTACK_H