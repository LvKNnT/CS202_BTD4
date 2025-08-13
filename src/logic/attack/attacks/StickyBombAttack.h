#ifndef STICKY_BOMB_ATTACK_H
#define STICKY_BOMB_ATTACK_H

#include "../Attack.h"

class StickyBombAttack : public Attack {
public:
    StickyBombAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~StickyBombAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;
    void update() override; 
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // STICKY_BOMB_ATTACK_H