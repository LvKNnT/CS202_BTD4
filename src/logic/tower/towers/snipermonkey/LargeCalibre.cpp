#include "LargeCalibre.h"
#include "../../../../core/Game.h"

#include "DeadlyPrecision.h"

LargeCalibre::LargeCalibre() 
    : Upgrade("Large Calibre", 1300, "Shots can pop through 7 layers of Bloon.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<DeadlyPrecision>(); // No further upgrade available
    tag = "Large Calibre";
}

LargeCalibre::LargeCalibre(const LargeCalibre& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> LargeCalibre::clone() const {
    return std::make_unique<LargeCalibre>(*this);
}

void LargeCalibre::loadTexture() {
    // Load the texture for Large Calibre upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/LargeCalibreUpgradeIcon.png");
}

void LargeCalibre::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 3;
}

std::unique_ptr<Upgrade> LargeCalibre::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}