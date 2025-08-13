#include "LongRangeDarts.h"
#include "../../../../core/Game.h"

#include "EnhancedEyesight.h"

LongRangeDarts::LongRangeDarts() 
    : Upgrade("Long Range Darts", 90, "Makes the Dart Monkey shoot further than normal.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<EnhancedEyesight>(); // Temporary lmao
    tag = "Long Range Darts";
}

LongRangeDarts::LongRangeDarts(const LongRangeDarts& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> LongRangeDarts::clone() const {
    return std::make_unique<LongRangeDarts>(*this);
}

void LongRangeDarts::loadTexture() {
    // Load the texture for Long Range Darts upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/LongRangeDartsUpgradeIcon.png");
}

void LongRangeDarts::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 32;
    attackBuff.lifeSpanRatio *= 1.35f;
}

std::unique_ptr<Upgrade> LongRangeDarts::buy() {
    return nextUpgrade->clone();
}