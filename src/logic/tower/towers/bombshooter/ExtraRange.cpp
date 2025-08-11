#include "ExtraRange.h"
#include "../../../../core/Game.h"

#include "FragBombs.h"

ExtraRange::ExtraRange() 
    : Upgrade("Extra Range", 200, "Increases attack range.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<FragBombs>(); // Temporary lmao
    tag = "Extra Range";
}

ExtraRange::ExtraRange(const ExtraRange& other)
    : Upgrade(other) {
    // Copy constructor implementation
}

std::unique_ptr<Upgrade> ExtraRange::clone() const {
    return std::make_unique<ExtraRange>(*this);
}

void ExtraRange::loadTexture() {
    // Load the texture for Extra Range upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/ExtraRangeUpgradeIcon.png");
}

void ExtraRange::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 48.0f;
    attackBuff.lifeSpanRatio *= 1.3f;
}

std::unique_ptr<Upgrade> ExtraRange::buy() {
    return nextUpgrade->clone();
}