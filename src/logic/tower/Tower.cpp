#include "Tower.h"
#include <iostream>

Tower::Tower(Vector2 position, Vector2 size, float rotation, TowerType type, int cost)
    : GameObject(position, size, rotation, "Tower"), type(type), cost(cost), targetPriority(TargetPriority::First), towerId(-1), popCount(0), attackBuff(AttackBuff()) {
    // Constructor implementation can be extended if needed
}

Tower::Tower(const Tower& other)
    : GameObject(other), type(other.type), cost(other.cost), upgradeCost(other.upgradeCost), targetPriority(other.targetPriority), towerId(other.towerId), popCount(other.popCount), info(other.info), attackBuff(other.attackBuff) {
    // Copy the attacks
    attacks.clear(); 
    for(const auto& attack : other.attacks) {
        attacks.push_back(attack->clone()); // Clone each attack
    }
    attackPattern = other.attackPattern ? other.attackPattern->clone() : nullptr; // Clone the attack pattern

    // Clone the upgrades
    upgradeTop = other.upgradeTop ? other.upgradeTop->clone() : std::make_unique<Upgrade>();
    upgradeMiddle = other.upgradeMiddle ? other.upgradeMiddle->clone() : std::make_unique<Upgrade>();
    upgradeBottom = other.upgradeBottom ? other.upgradeBottom->clone() : std::make_unique<Upgrade>();
}