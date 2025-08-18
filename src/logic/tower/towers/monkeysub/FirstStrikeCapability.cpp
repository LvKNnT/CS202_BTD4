#include "FirstStrikeCapability.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/FirstStrikeCapabilitySkill.h"

#include "PreEmptiveStrike.h"

FirstStrikeCapability::FirstStrikeCapability() 
    : Upgrade("First Strike Capability", 13000, "First Strike Ability: A devastating missile strike targeting the largest bloon on screen, plus splash damage.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<PreEmptiveStrike>(); 
    tag = "First Strike Capability";
}

FirstStrikeCapability::FirstStrikeCapability(const FirstStrikeCapability& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FirstStrikeCapability::clone() const {
    return std::make_unique<FirstStrikeCapability>(*this);
}

void FirstStrikeCapability::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/FirstStrikeCapabilityUpgradeIcon.png");
}

void FirstStrikeCapability::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    skill = std::make_unique<FirstStrikeCapabilitySkill>();
}

std::unique_ptr<Upgrade> FirstStrikeCapability::buy() {
    return nextUpgrade->clone();
}