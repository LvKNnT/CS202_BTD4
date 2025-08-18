#include "SubCommander.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/SubCommanderSkill.h"

SubCommander::SubCommander() 
    : Upgrade("Sub Commander", 25000, "Adds extra pierce and damage to Commander and all Subs in its radius.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Sub Commander";
}

SubCommander::SubCommander(const SubCommander& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SubCommander::clone() const {
    return std::make_unique<SubCommander>(*this);
}

void SubCommander::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/SubCommanderUpgradeIcon.png");
}

void SubCommander::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.5;

    passiveSkills.push_back(std::make_unique<SubCommanderSkill>());
}

std::unique_ptr<Upgrade> SubCommander::buy() {
    return nextUpgrade->clone();
}