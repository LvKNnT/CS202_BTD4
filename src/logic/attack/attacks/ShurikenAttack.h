#ifndef SHURIKENATTACK_H
#define SHURIKENATTACK_H

#include "../Attack.h"

class ShurikenAttack : public Attack {
public:
    ShurikenAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~ShurikenAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const override;
    void update() override; 
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // SHURIKENATTACK_H