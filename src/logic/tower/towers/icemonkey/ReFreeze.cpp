#include "ReFreeze.h"
#include "../../../../core/Game.h"

#include "CryoCannon.h"

ReFreeze::ReFreeze() 
    : Upgrade("Re-Freeze", 200, "Can re-freeze Bloons that are already frozen.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<CryoCannon>(); // Temporary lmao
    tag = "Re-Freeze";
}

ReFreeze::ReFreeze(const ReFreeze& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ReFreeze::clone() const {
    return std::make_unique<ReFreeze>(*this);
}

void ReFreeze::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/Re-FreezeUpgradeIcon.png");
}

void ReFreeze::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canFrozen = true;
}

std::unique_ptr<Upgrade> ReFreeze::buy() {
    return nextUpgrade->clone();
}