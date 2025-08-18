#include "HeatTippedDarts.h"
#include "../../../../core/Game.h"

#include "BallisticMissile.h"

HeatTippedDarts::HeatTippedDarts() 
    : Upgrade("Heat-tipped Darts", 300, "Heat tipped darts allow the Monkey Sub to pop Frozen and Lead Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<BallisticMissile>(); // Temporary lmao
    tag = "Heat-tipped Darts";
}

HeatTippedDarts::HeatTippedDarts(const HeatTippedDarts& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> HeatTippedDarts::clone() const {
    return std::make_unique<HeatTippedDarts>(*this);
}

void HeatTippedDarts::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/HeatTippedDartsUpgradeIcon.png");
}

void HeatTippedDarts::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canLead = true; // Allow the darts to pop lead bloons
    attackBuff.properties.canFrozen = true; // Allow the darts to pop black bloons
}

std::unique_ptr<Upgrade> HeatTippedDarts::buy() {
    return nextUpgrade->clone();
}