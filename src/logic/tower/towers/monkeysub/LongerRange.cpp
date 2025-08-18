#include "LongerRange.h"
#include "../../../../core/Game.h"

#include "AdvancedIntel.h"

LongerRange::LongerRange() 
    : Upgrade("Longer Range", 130, "Increases attack range.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<AdvancedIntel>(); // Temporary lmao
    tag = "Longer Range";
}

LongerRange::LongerRange(const LongerRange& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> LongerRange::clone() const {
    return std::make_unique<LongerRange>(*this);
}

void LongerRange::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/LongerRangeUpgradeIcon.png");
}

void LongerRange::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 20.0f; // Increase the attack range by 20 units
}

std::unique_ptr<Upgrade> LongerRange::buy() {
    return nextUpgrade->clone();
}