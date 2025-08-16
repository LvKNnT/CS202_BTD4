#include "AbsoluteZero.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/AbsoluteZeroPassiveSkill.h"
#include "../../../skill/skills/AbsoluteZeroSkill.h"

AbsoluteZero::AbsoluteZero() 
    : Upgrade("Absolute Zero", 16000, "Ability is so cold it freezes all regular Bloons for longer, including White, Zebra, and Camo, slows MOAB-class longer, and greatly increases the attack speed of all Ice Monkeys for the duration.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Absolute Zero";
}

AbsoluteZero::AbsoluteZero(const AbsoluteZero& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> AbsoluteZero::clone() const {
    return std::make_unique<AbsoluteZero>(*this);
}

void AbsoluteZero::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/AbsoluteZeroUpgradeIcon.png");
}

void AbsoluteZero::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.pierce += 255;
    attackBuff.range += 20.0f;

    skill = std::make_unique<AbsoluteZeroSkill>();

    for(auto& passiveSkill : passiveSkills) {
        if (passiveSkill->getName() == "Arctic Wind Skill") {
            passiveSkill = std::make_unique<AbsoluteZeroPassiveSkill>();
            break;
        }
    }
}

std::unique_ptr<Upgrade> AbsoluteZero::buy() {
    return nextUpgrade->clone();
}