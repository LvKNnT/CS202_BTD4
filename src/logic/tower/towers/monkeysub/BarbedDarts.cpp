#include "BarbedDarts.h"
#include "../../../../core/Game.h"

#include "HeatTippedDarts.h"

BarbedDarts::BarbedDarts() 
    : Upgrade("Barbed Darts", 450, "Sub's darts can pop an additional 3 bloons each. Enhances pierce of other weapons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<HeatTippedDarts>(); // Temporary lmao
    tag = "Barbed Darts";
}

BarbedDarts::BarbedDarts(const BarbedDarts& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BarbedDarts::clone() const {
    return std::make_unique<BarbedDarts>(*this);
}

void BarbedDarts::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/BarbedDartsUpgradeIcon.png");
}

void BarbedDarts::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.pierce += 1;
}

std::unique_ptr<Upgrade> BarbedDarts::buy() {
    return nextUpgrade->clone();
}