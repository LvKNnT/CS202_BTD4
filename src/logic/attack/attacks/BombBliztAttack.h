#ifndef BOMB_BLIZT_ATTACK_H
#define BOMB_BLIZT_ATTACK_H

#include "../Attack.h"

class BombBliztAttack : public Attack {
public:
    BombBliztAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    
    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;

    void update() override;
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // BOMB_BLIZT_ATTACK_H