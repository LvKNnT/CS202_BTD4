#include "FlashBomb.h"
#include "../../../../core/Game.h"

#include "StickyBomb.h"

FlashBomb::FlashBomb() 
    : Upgrade("Flash Bomb", 2250, "Combination attack! Alternates flash bombs that stun many Bloons and shuriken deal increased damage to stunned targets.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<StickyBomb>(); // Temporary lmao
    tag = "Flash Bomb";
}

FlashBomb::FlashBomb(const FlashBomb& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FlashBomb::clone() const {
    return std::make_unique<FlashBomb>(*this);
}

void FlashBomb::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/FlashBombUpgradeIcon.png");
}

void FlashBomb::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto& attack : attacks) {
    }
}

std::unique_ptr<Upgrade> FlashBomb::buy() {
    return nextUpgrade->clone();
}