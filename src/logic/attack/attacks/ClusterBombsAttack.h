#ifndef CLUSTER_BOMBS_ATTACK_H
#define CLUSTER_BOMBS_ATTACK_H

#include "../Attack.h"

class ClusterBombsAttack : public Attack {
public:
    ClusterBombsAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    
    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const override;

    void update() override;
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;
};

#endif // CLUSTER_BOMBS_ATTACK_H