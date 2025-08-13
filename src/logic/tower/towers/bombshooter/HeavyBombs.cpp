#include "HeavyBombs.h"
#include "../../../../core/Game.h"

#include "ReallyBigBombs.h"

HeavyBombs::HeavyBombs() 
    : Upgrade("Heavy Bombs", 650, "Heavy duty bombs can smash through 2 layers of Bloon at once and pop more Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ReallyBigBombs>(); // Temporary lmao
    tag = "Heavy Bombs";
}

HeavyBombs::HeavyBombs(const HeavyBombs& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> HeavyBombs::clone() const {
    return std::make_unique<HeavyBombs>(*this);
}

void HeavyBombs::loadTexture() {
    // Load the texture for Heavy Bombs upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/HeavyBombsUpgradeIcon.png");
}

void HeavyBombs::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 1; 
    attackBuff.pierce += 10; 
}

std::unique_ptr<Upgrade> HeavyBombs::buy() {
    return nextUpgrade->clone();
}

