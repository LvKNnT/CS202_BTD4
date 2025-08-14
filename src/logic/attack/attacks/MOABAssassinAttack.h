#ifndef MOAB_ASSASSIN_ATTACK_H
#define MOAB_ASSASSIN_ATTACK_H

#include "../Attack.h"

class MOABAssassinAttack : public Attack {
public:
    MOABAssassinAttack(Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~MOABAssassinAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const override;
    void update() override; 
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // MOAB_ASSASSIN_ATTACK_H