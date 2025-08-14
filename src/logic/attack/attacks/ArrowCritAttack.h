#ifndef ARROW_CRIT_ATTACK_H
#define ARROW_CRIT_ATTACK_H

#include "../Attack.h"

class ArrowCritAttack : public Attack {
private:
    int counter;
    int maxCounter;

public:
    ArrowCritAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, int maxCounter);
    ArrowCritAttack(const ArrowCritAttack& other) = default;
    ~ArrowCritAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const override;
    void update() override;
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // ARROW_CRIT_ATTACK_H