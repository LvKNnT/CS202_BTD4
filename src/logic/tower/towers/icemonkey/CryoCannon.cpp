#include "CryoCannon.h"
#include "../../../../core/Game.h"

#include "Icicles.h"

CryoCannon::CryoCannon() 
    : Upgrade("Cryo Cannon", 1900, "Rapidly shoots smaller ice bombs over longer range.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Icicles>(); // Temporary lmao
    tag = "Cryo Cannon";
}

CryoCannon::CryoCannon(const CryoCannon& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> CryoCannon::clone() const {
    return std::make_unique<CryoCannon>(*this);
}

void CryoCannon::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/CryoCannonUpgradeIcon.png");
}

void CryoCannon::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.5f; 
    attackBuff.range += 32.0f;
}

std::unique_ptr<Upgrade> CryoCannon::buy() {
    return nextUpgrade->clone();
}