#include "LargerRadius.h"
#include "../../../../core/Game.h"

#include "ReFreeze.h"

LargerRadius::LargerRadius() 
    : Upgrade("Larger Radius", 150, "Larger freeze area.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ReFreeze>(); // Temporary lmao
    tag = "Larger Radius";
}

LargerRadius::LargerRadius(const LargerRadius& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> LargerRadius::clone() const {
    return std::make_unique<LargerRadius>(*this);
}

void LargerRadius::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/LargerRadiusUpgradeIcon.png");
}

void LargerRadius::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 14.0f; // Increase the range of the attack
}

std::unique_ptr<Upgrade> LargerRadius::buy() {
    return nextUpgrade->clone();
}