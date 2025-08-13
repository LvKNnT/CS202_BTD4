#include "DeadlyPrecision.h"
#include "../../../../core/Game.h"

#include "MaimMOAB.h"

DeadlyPrecision::DeadlyPrecision() 
    : Upgrade("Deadly Precision", 2500, "20 damage per shot, plus bonus damage to Ceramics.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MaimMOAB>(); // No further upgrade available
    tag = "Deadly Precision";
}

DeadlyPrecision::DeadlyPrecision(const DeadlyPrecision& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> DeadlyPrecision::clone() const {
    return std::make_unique<DeadlyPrecision>(*this);
}

void DeadlyPrecision::loadTexture() {
    // Load the texture for Deadly Precision upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/DeadlyPrecisionUpgradeIcon.png");
}

void DeadlyPrecision::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 13;
    attackBuff.extraNormalDebuff.bonusDamage += 15; // Increase bonus damage for normal bloons
}

std::unique_ptr<Upgrade> DeadlyPrecision::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}