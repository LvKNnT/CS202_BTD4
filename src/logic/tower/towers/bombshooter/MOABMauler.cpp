#include "MOABMauler.h"
#include "../../../../core/Game.h"

#include "MOABAssassin.h"

MOABMauler::MOABMauler() 
    : Upgrade("MOAB Mauler", 1000, "MOAB Maulers do much more damage to MOAB-Class Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MOABAssassin>(); // Temporary lmao
    tag = "MOAB Mauler";
}

MOABMauler::MOABMauler(const MOABMauler& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MOABMauler::clone() const {
    return std::make_unique<MOABMauler>(*this);
}

void MOABMauler::loadTexture() {
    // Load the texture for MOAB Mauler upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/MOABMaulerUpgradeIcon.png");
}

void MOABMauler::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 20.0f;
    attackBuff.extraMoabDebuff.bonusDamage += 15; // Increase bonus damage to MOAB-Class Bloons
}

std::unique_ptr<Upgrade> MOABMauler::buy() {
    return nextUpgrade->clone();
}
