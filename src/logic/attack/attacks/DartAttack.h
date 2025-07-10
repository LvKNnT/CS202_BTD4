#ifndef DARTATTACK_H
#define DARTATTACK_H

#include "../Attack.h"
#include "../../bullet/bullets/Dart.h"

class DartAttack : public Attack {
public:
    DartAttack(float range, float cooldown, Vector2 position, int damage, int speed, int pierce, float lifeSpan);
    ~DartAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Vector2& targetPosition) const override;
    void update(BulletManager& bulletManager, const Vector2& targetPosition) override;
};

#endif // DARTATTACK_H