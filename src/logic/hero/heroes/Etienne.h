#ifndef ETIENNE_H
#define ETIENNE_H

#include "../Hero.h"

class Etienne : public Hero {
public:
    Etienne();
    ~Etienne() override = default;

    std::unique_ptr<Hero> clone() const override;

    // Override all methods from Hero
    HeroType getType() const override;
    LogicInfo getInfo() const override;
    TowerModifies getModifies(TowerModifies towerModifies) const override;
    AttackBuff getAttackBuff() const override;
};

#endif // ETIENNE_H