#ifndef CALTROPSATTACK_H
#define CALTROPSATTACK_H

#include "../Attack.h"

class CaltropsAttack : public Attack {
public:
    CaltropsAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties Properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff);
    ~CaltropsAttack() override = default;

    std::unique_ptr<Attack> clone() const override;

    bool isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const override;
    void update() override; 
    void update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) override;

    bool isRotateTower() const override; // CaltropsAttack does not require rotation, so it returns true
    float getRotateTower(float rotation) override; // CaltropsAttack does not require rotation, so it returns false

private:
    float rotation;
};

#endif // CALTROPSATTACK_H