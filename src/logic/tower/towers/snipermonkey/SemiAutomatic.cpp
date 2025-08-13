#include "SemiAutomatic.h"
#include "../../../../core/Game.h"

#include "FullAutoRifle.h"

SemiAutomatic::SemiAutomatic() 
    : Upgrade("Semi-Automatic", 2900, "Attacks 3x as fast!") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<FullAutoRifle>(); // No further upgrade available
    tag = "Semi-Automatic";
}

SemiAutomatic::SemiAutomatic(const SemiAutomatic& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SemiAutomatic::clone() const {
    return std::make_unique<SemiAutomatic>(*this);
}

void SemiAutomatic::loadTexture() {
    // Load the texture for Semi Automatic upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/SemiAutomaticUpgradeIcon.png");
}

void SemiAutomatic::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.pierce *= 1.0f / 3.0f;
}

std::unique_ptr<Upgrade> SemiAutomatic::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}