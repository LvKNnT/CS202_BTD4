#include "Rosalia.h"

Rosalia::Rosalia() {
    // Initialize Rosalia hero properties
    info["name"] = "Rosalia";
    info["description"] = "Your towers cost lesser.";
    info["type"] = "Hero";
}

HeroType Rosalia::getType() const {
    return HeroType::Rosalia;
}

LogicInfo Rosalia::getInfo() const {
    return info;
}

TowerModifies Rosalia::getModifies(TowerModifies towerModifies) const {
    // no change
    return towerModifies;
}

AttackBuff Rosalia::getAttackBuff() const {
    AttackBuff buff = AttackBuff();
    buff.damage += 1;
    return buff;
}

