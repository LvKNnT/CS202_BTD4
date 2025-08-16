#ifndef HERO_H
#define HERO_H

#include "HeroUnits.h"
#include "../level/TowerModifies.h"
#include "../attack/AttackUnits.h"
#include "../LogicInfo.h"

class Hero {
protected:
    LogicInfo info;

public:
    Hero() = default;
    Hero(const Hero& other) = default;
    virtual ~Hero() = default;

    Hero& operator=(const Hero& other);
    virtual std::unique_ptr<Hero> clone() const = 0;
    
    // Getters
    virtual HeroType getType() const = 0;
    virtual LogicInfo getInfo() const = 0;
    virtual TowerModifies getModifies(TowerModifies towerModifies) const = 0;
    virtual AttackBuff getAttackBuff() const = 0;
};

#endif // HERO_H