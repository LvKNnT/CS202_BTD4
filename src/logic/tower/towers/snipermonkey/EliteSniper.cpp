#include "EliteSniper.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/EliteSniperSkill.h"
#include "../../../skill/skills/EliteSniperPassiveSkill.h"

EliteSniper::EliteSniper() 
    : Upgrade("Elite Sniper", 14000, "Supply Drop gives much more cash. Provide faster reload to all snipers.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // No further upgrade available
    tag = "Elite Sniper";
}

EliteSniper::EliteSniper(const EliteSniper& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> EliteSniper::clone() const {
    return std::make_unique<EliteSniper>(*this);
}

void EliteSniper::loadTexture() {
    // Load the texture for Elite Sniper upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/EliteSniperUpgradeIcon.png");
}

void EliteSniper::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.4f;
    
    skill = std::make_unique<EliteSniperSkill>();
    passiveSkills.push_back(std::make_unique<EliteSniperPassiveSkill>());
}

std::unique_ptr<Upgrade> EliteSniper::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}
