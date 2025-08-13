#include "MissileLauncher.h"
#include "../../../../core/Game.h"

#include "MOABMauler.h"

MissileLauncher::MissileLauncher() 
    : Upgrade("Missile Launcher", 400, "Exchanges bombs for missiles, which fire faster, fly faster, and increase range.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MOABMauler>(); // Temporary lmao
    tag = "Missile Launcher";
}

MissileLauncher::MissileLauncher(const MissileLauncher& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MissileLauncher::clone() const {
    return std::make_unique<MissileLauncher>(*this);
}

void MissileLauncher::loadTexture() {
    // Load the texture for Missile Launcher upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/MissileLauncherUpgradeIcon.png");
}

void MissileLauncher::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.speedRatio *= 1.5f; // Increase speed by 50%
    attackBuff.rangeRatio *= 1.1f; // Increase range by 10%
    attackBuff.lifeSpanRatio *= 1.1f; // Increase lifespan by 10%
    attackBuff.cooldownRatio *= 0.55f / 0.75f; // Reduce cooldown by 26.67% 
}

std::unique_ptr<Upgrade> MissileLauncher::buy() {
    return nextUpgrade->clone();
}