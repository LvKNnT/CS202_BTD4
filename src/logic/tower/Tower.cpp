#include "Tower.h"
#include <iostream>

Tower::Tower(Vector2 position, Vector2 size, float rotation, TowerType type, int cost)
    : GameObject(position, size, rotation, "Tower"), type(type), cost(cost), targetPriority(TargetPriority::First), canSeeCamo(false), towerId(-1), popCount(0) {
    // Constructor implementation can be extended if needed
}

Tower::Tower(const Tower& other)
    : GameObject(other), type(other.type), cost(other.cost), upgradeCost(other.upgradeCost), targetPriority(other.targetPriority), towerId(other.towerId), popCount(other.popCount), info(other.info) {
    // Copy the attacks
    attacks.clear(); 
    for(const auto& attack : other.attacks) {
        attacks.push_back(attack->clone()); // Clone each attack
    }

    // Clone the upgrades
    upgradeTop = other.upgradeTop ? other.upgradeTop->clone() : std::make_unique<Upgrade>();
    upgradeMiddle = other.upgradeMiddle ? other.upgradeMiddle->clone() : std::make_unique<Upgrade>();
    upgradeBottom = other.upgradeBottom ? other.upgradeBottom->clone() : std::make_unique<Upgrade>();
}

void Tower::unLoad() {
    UnloadTexture(texture);
}