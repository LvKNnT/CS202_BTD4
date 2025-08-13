#include "EvenFasterFiring.h"
#include "../../../../core/Game.h"

#include "SemiAutomatic.h"

EvenFasterFiring::EvenFasterFiring() 
    : Upgrade("Even Faster Firing", 450, "Shoots even faster!") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SemiAutomatic>(); // No further upgrade available
    tag = "Even Faster Firing";
}

EvenFasterFiring::EvenFasterFiring(const EvenFasterFiring& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> EvenFasterFiring::clone() const {
    return std::make_unique<EvenFasterFiring>(*this);
}

void EvenFasterFiring::loadTexture() {
    // Load the texture for Even Faster Firing upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/EvenFasterFiringUpgradeIcon.png");
}

void EvenFasterFiring::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.7f; // Further reduce cooldown ratio for even faster firing
}

std::unique_ptr<Upgrade> EvenFasterFiring::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}