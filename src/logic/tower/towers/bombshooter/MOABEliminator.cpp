#include "MOABEliminator.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/MOABEliminatorSkill.h"

MOABEliminator::MOABEliminator() 
    : Upgrade("MOAB Eliminator", 28000, "Massive damage to MOABs and Assassinate ability deals 6x damage with a short cooldown.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "MOAB Eliminator";
}

MOABEliminator::MOABEliminator(const MOABEliminator& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MOABEliminator::clone() const {
    return std::make_unique<MOABEliminator>(*this);
}

void MOABEliminator::loadTexture() {
    // Load the texture for MOAB Eliminator upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/MOABEliminatorUpgradeIcon.png");
}

void MOABEliminator::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 30.0f; 
    attackBuff.extraMoabDebuff.bonusDamage += 69; 

    skill = std::make_unique<MOABEliminatorSkill>();
}

std::unique_ptr<Upgrade> MOABEliminator::buy() {
    return nextUpgrade->clone();
}