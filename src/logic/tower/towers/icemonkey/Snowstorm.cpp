#include "Snowstorm.h"
#include "../../../../core/Game.h"

#include "AbsoluteZero.h"

#include "../../../skill/skills/SnowstormSkill.h"

Snowstorm::Snowstorm() 
    : Upgrade("Snowstorm", 4000, "Snowstorm Ability: Freezes all regular Bloons on screen, briefly freezes White, Zebra, and Camo, and slows MOAB-class.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<AbsoluteZero>(); // Temporary lmao
    tag = "Snowstorm";
}

Snowstorm::Snowstorm(const Snowstorm& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Snowstorm::clone() const {
    return std::make_unique<Snowstorm>(*this);
}

void Snowstorm::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/SnowstormUpgradeIcon.png");
}

void Snowstorm::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 20.0f;    

    skill = std::make_unique<SnowstormSkill>();
}

std::unique_ptr<Upgrade> Snowstorm::buy() {
    return nextUpgrade->clone();
}