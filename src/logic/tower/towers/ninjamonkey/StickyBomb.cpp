#include "StickyBomb.h"
#include "../../../../core/Game.h"

#include "MasterBomber.h"

StickyBomb::StickyBomb() 
    : Upgrade("Sticky Bomb", 5000, "Throws powerful timed charges at MOAB-Class Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MasterBomber>(); // Temporary lmao
    tag = "Sticky Bomb";
}

StickyBomb::StickyBomb(const StickyBomb& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> StickyBomb::clone() const {
    return std::make_unique<StickyBomb>(*this);
}

void StickyBomb::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/StickyBombUpgradeIcon.png");
}

void StickyBomb::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto& attack : attacks) {
    }
}

std::unique_ptr<Upgrade> StickyBomb::buy() {
    return nextUpgrade->clone();
}