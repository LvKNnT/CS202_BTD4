#include "FastFiring.h"
#include "../../../../core/Game.h"

#include "EvenFasterFiring.h"

FastFiring::FastFiring() 
    : Upgrade("Fast Firing", 450, "Shoots faster than normal.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<EvenFasterFiring>(); // No further upgrade available
    tag = "Fast Firing";
}

FastFiring::FastFiring(const FastFiring& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FastFiring::clone() const {
    return std::make_unique<FastFiring>(*this);
}

void FastFiring::loadTexture() {
    // Load the texture for Fast Firing upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/FastFiringUpgradeIcon.png");
}

void FastFiring::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.7f;
}

std::unique_ptr<Upgrade> FastFiring::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}
