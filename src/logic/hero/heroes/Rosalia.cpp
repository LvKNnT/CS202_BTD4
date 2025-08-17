#include "Rosalia.h"

Rosalia::Rosalia() {
    // Initialize Rosalia hero properties
    info["name"] = "Rosalia";
    info["description"] = "Your towers deal more damager(+1 damage).";
    info["type"] = "Hero";
}

std::unique_ptr<Hero> Rosalia::clone() const {
    return std::make_unique<Rosalia>(*this);
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

