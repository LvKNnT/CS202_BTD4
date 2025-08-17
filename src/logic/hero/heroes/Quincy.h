#ifndef QUINCY_H
#define QUINCY_H

#include "../Hero.h"

class Quincy : public Hero {
public:
    Quincy();
    ~Quincy() override = default;

    std::unique_ptr<Hero> clone() const override;

    // Override all methods from Hero
    HeroType getType() const override;
    LogicInfo getInfo() const override;
    TowerModifies getModifies(TowerModifies towerModifies) const override;
    AttackBuff getAttackBuff() const override;
};

#endif // QUINCY_H