#ifndef ROSALIA_H
#define ROSALIA_H

#include "../Hero.h"

class Rosalia : public Hero {
public:
    Rosalia();
    ~Rosalia() override = default;

    std::unique_ptr<Hero> clone() const override;

    // Override all methods from Hero
    HeroType getType() const override;
    LogicInfo getInfo() const override;
    TowerModifies getModifies(TowerModifies towerModifies) const override;
    AttackBuff getAttackBuff() const override;
};

#endif // ROSALIA_H