#include "EliteDefender.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/EliteDefenderSkill.h"
#include "../../../skill/skills/EliteDefenderPassiveSkill.h"

EliteDefender::EliteDefender() 
    : Upgrade("Elite Defender", 14700, "Fires super fast and does more damage to MOAB-class Bloons. Fires faster the further the Bloons are along the track. Gains 4x attack speed briefly on losing lives.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // No further upgrade available
    tag = "Elite Defender";
}

EliteDefender::EliteDefender(const EliteDefender& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> EliteDefender::clone() const {
    return std::make_unique<EliteDefender>(*this);
}

void EliteDefender::loadTexture() {
    // Load the texture for Elite Defender upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/EliteDefenderUpgradeIcon.png");
}

void EliteDefender::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.5f; 
    attackBuff.extraNormalDebuff.bonusDamage += 1;
    attackBuff.extraMoabDebuff.bonusDamage += 2;

    passiveSkills.push_back(std::make_unique<EliteDefenderSkill>());
    passiveSkills.push_back(std::make_unique<EliteDefenderPassiveSkill>());
}

std::unique_ptr<Upgrade> EliteDefender::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}