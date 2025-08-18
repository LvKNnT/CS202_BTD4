#include "AdvancedIntel.h"
#include "../../../../core/Game.h"

#include "SubmergeAndSupport.h"

AdvancedIntel::AdvancedIntel() 
    : Upgrade("Advanced Intel", 500, "Allows long range targeting of Bloons in radius of your other towers.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SubmergeAndSupport>(); // Temporary lmao
    tag = "Advanced Intel";
}

AdvancedIntel::AdvancedIntel(const AdvancedIntel& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> AdvancedIntel::clone() const {
    return std::make_unique<AdvancedIntel>(*this);
}

void AdvancedIntel::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/AdvancedIntelUpgradeIcon.png");
}

void AdvancedIntel::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.rangeRatio *= 3.0f;
}

std::unique_ptr<Upgrade> AdvancedIntel::buy() {
    return nextUpgrade->clone();
}