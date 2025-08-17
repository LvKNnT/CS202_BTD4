#include "Etienne.h"

Etienne::Etienne() {
    // Initialize Etienne hero properties
    info["name"] = "Etienne";
    info["description"] = "Your towers cost lesser.";
    info["type"] = "Hero";
}

std::unique_ptr<Hero> Etienne::clone() const {
    return std::make_unique<Etienne>(*this);
}

HeroType Etienne::getType() const {
    return HeroType::Etienne;
}

LogicInfo Etienne::getInfo() const {
    return info;
}

TowerModifies Etienne::getModifies(TowerModifies towerModifies) const {
    // no change
    return towerModifies;
}

AttackBuff Etienne::getAttackBuff() const {
    AttackBuff buff = AttackBuff();
    buff.rangeRatio *= 1.1f; // Etienne increases range of attacks by 10%
    return buff;
}

