#ifndef BENJAMIN_H
#define BENJAMIN_H

#include "../Hero.h"

class Benjamin : public Hero {
public:
    Benjamin();
    ~Benjamin() override = default;

    std::unique_ptr<Hero> clone() const override;

    // Override all methods from Hero
    HeroType getType() const override;
    LogicInfo getInfo() const override;
    TowerModifies getModifies(TowerModifies towerModifies) const override;
    AttackBuff getAttackBuff() const override;
};

#endif // BENJAMIN_H