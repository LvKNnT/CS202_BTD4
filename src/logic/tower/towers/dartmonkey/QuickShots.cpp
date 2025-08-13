#include "QuickShots.h"
#include "../../../../core/Game.h"

#include "VeryQuickShots.h"

QuickShots::QuickShots() 
    : Upgrade("Quick Shots", 100, "Shoots 15% faster.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<VeryQuickShots>(); // Temporary lmao
    tag = "Quick Shots";
}

QuickShots::QuickShots(const QuickShots& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> QuickShots::clone() const {
    return std::make_unique<QuickShots>(*this);
}

void QuickShots::loadTexture() {
    // Load the texture for Razor Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/QuickShotsUpgradeIcon.png");
}

void QuickShots::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.85f;
}

std::unique_ptr<Upgrade> QuickShots::buy() {
    return nextUpgrade->clone();
}