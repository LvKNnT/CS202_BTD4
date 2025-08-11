#include "MOABAssassin.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/MOABAssassinSkill.h"

#include "MOABEliminator.h"

MOABAssassin::MOABAssassin() 
    : Upgrade("MOAB Assassin", 5000, "Assassinates a MOAB-Class Bloon instantly, but has a long cooldown.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MOABEliminator>(); // Temporary lmao
    tag = "MOAB Assassin";
}

MOABAssassin::MOABAssassin(const MOABAssassin& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MOABAssassin::clone() const {
    return std::make_unique<MOABAssassin>(*this);
}

void MOABAssassin::loadTexture() {
    // Load the texture for MOAB Assassin upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/MOABAssassinUpgradeIcon.png");
}

void MOABAssassin::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 20.0f; 
    attackBuff.lifeSpanRatio *= 1.125f; // Increase lifespan by 50%
    attackBuff.extraMoabDebuff.bonusDamage += 15; 
    attackBuff.extraNormalDebuff.bonusDamage += 4; 

    skill = std::make_unique<MOABAssassinSkill>();
}

std::unique_ptr<Upgrade> MOABAssassin::buy() {
    return nextUpgrade->clone();
}