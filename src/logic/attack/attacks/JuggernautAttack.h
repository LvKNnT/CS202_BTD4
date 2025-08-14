#ifndef JUGGERNAUT_ATTACK_H
#define JUGGERNAUT_ATTACK_H

#include "../Attack.h"

class JuggernautAttack : public Attack {
public:
    JuggernautAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~JuggernautAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const override;
    void update() override;
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // JUGGERNAUT_ATTACK_H