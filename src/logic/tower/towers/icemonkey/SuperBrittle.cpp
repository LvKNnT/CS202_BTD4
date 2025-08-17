#include "SuperBrittle.h"
#include "../../../../core/Game.h"

SuperBrittle::SuperBrittle() 
    : Upgrade("Super Brittle", 28000, "Bloons take huge damage while frozen including MOAB-class Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Super Brittle";
}

SuperBrittle::SuperBrittle(const SuperBrittle& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SuperBrittle::clone() const {
    return std::make_unique<SuperBrittle>(*this);
}

void SuperBrittle::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/SuperBrittleUpgradeIcon.png");
}

void SuperBrittle::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canWhite = true;
    attackBuff.cooldownRatio *= 2.0f / 3.0f; 
    attackBuff.extraNormalDebuff.bonusOnHitDamage += 3;
    attackBuff.extraMoabDebuff.bonusOnHitDamage += 4;
    attackBuff.extraMoabDebuff += BloonDebuff().getISlow(0.25, 10);
}

std::unique_ptr<Upgrade> SuperBrittle::buy() {
    return nextUpgrade->clone();
}