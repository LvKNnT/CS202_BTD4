#include "Quincy.h"

Quincy::Quincy() {
    // Initialize Quincy hero properties
    info["name"] = "Quincy";
    info["description"] = "Your towers will shoot faster.";
    info["type"] = "Hero";
}

HeroType Quincy::getType() const {
    return HeroType::Quincy;
}

LogicInfo Quincy::getInfo() const {
    return info;
}

TowerModifies Quincy::getModifies(TowerModifies towerModifies) const {
    // no change
    return towerModifies;
}

AttackBuff Quincy::getAttackBuff() const {
    AttackBuff buff = AttackBuff();
    buff.cooldownRatio *= 0.9f; // Quincy reduces cooldown of attacks by 10%
    return buff;
}

