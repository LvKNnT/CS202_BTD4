#include "FullMetalJacket.h"
#include "../../../../core/Game.h"

#include "LargeCalibre.h"

FullMetalJacket::FullMetalJacket() 
    : Upgrade("Full Metal Jacket", 350, "Shots pop through 4 layers of bloon, and both bullets and shrapnel can pop Lead and Frozen Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<LargeCalibre>(); // No further upgrade available
    tag = "Full Metal Jacket";
}

FullMetalJacket::FullMetalJacket(const FullMetalJacket& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FullMetalJacket::clone() const {
    return std::make_unique<FullMetalJacket>(*this);
}

void FullMetalJacket::loadTexture() {
    // Load the texture for Full Metal Jacket upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/FullMetalJacketUpgradeIcon.png");
}

void FullMetalJacket::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 2;
    attackBuff.properties.canLead = true; // Allow bullets to hit Lead bloons
    attackBuff.properties.canFrozen = true; // Allow bullets to hit Frozen bloons
}

std::unique_ptr<Upgrade> FullMetalJacket::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}