#include "ArcticWind.h"
#include "../../../../core/Game.h"

#include "Snowstorm.h"

#include "../../../skill/skills/ArcticWindSkill.h"

ArcticWind::ArcticWind() 
    : Upgrade("Arctic Wind", 2750, "Gains a super cold aura that slows Bloons and freezes water nearby.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Snowstorm>(); // Temporary lmao
    tag = "Arctic Wind";
}

ArcticWind::ArcticWind(const ArcticWind& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ArcticWind::clone() const {
    return std::make_unique<ArcticWind>(*this);
}

void ArcticWind::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/ArcticWindUpgradeIcon.png");
}

void ArcticWind::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    passiveSkills.push_back(std::make_unique<ArcticWindSkill>());
}

std::unique_ptr<Upgrade> ArcticWind::buy() {
    return nextUpgrade->clone();
}