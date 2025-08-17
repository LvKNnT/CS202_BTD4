#include "Benjamin.h"

Benjamin::Benjamin() {
    // Initialize Benjamin hero properties
    info["name"] = "Benjamin";
    info["description"] = "Your towers cost lesser.";
    info["type"] = "Hero";
}

std::unique_ptr<Hero> Benjamin::clone() const {
    return std::make_unique<Benjamin>(*this);
}

HeroType Benjamin::getType() const {
    return HeroType::Benjamin;
}

LogicInfo Benjamin::getInfo() const {
    return info;
}

TowerModifies Benjamin::getModifies(TowerModifies towerModifies) const {
    // no change
    towerModifies.cost *= 0.9f; // Benjamin reduces cost of towers by 10%
    towerModifies.upgradeCost *= 0.9f; // Benjamin reduces upgrade cost
    return towerModifies;
}

AttackBuff Benjamin::getAttackBuff() const {
    AttackBuff buff = AttackBuff();
    // no buff
    return buff;
}

