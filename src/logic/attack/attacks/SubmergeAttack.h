#ifndef SUBMERGE_ATTACK_H
#define SUBMERGE_ATTACK_H

#include "../Attack.h"

class SubmergeAttack : public Attack {
public:
    SubmergeAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~SubmergeAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const override;
    void update() override; 
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // SUBMERGE_ATTACK_H