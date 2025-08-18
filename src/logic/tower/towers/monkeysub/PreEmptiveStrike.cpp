#include "PreEmptiveStrike.h"
#include "../../../../core/Game.h"

PreEmptiveStrike::PreEmptiveStrike() 
    : Upgrade("Pre-Emptive Strike", 29000, "Automatically triggers a powerful missile attack whenever MOAB-Class Bloon spawns from the Bloon entrance.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Pre-Emptive Strike";
}

PreEmptiveStrike::PreEmptiveStrike(const PreEmptiveStrike& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> PreEmptiveStrike::clone() const {
    return std::make_unique<PreEmptiveStrike>(*this);
}

void PreEmptiveStrike::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/PreEmptiveStrikeUpgradeIcon.png");
}

void PreEmptiveStrike::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.extraNormalDebuff.bonusDamage += 17;
    attackBuff.extraMoabDebuff.bonusDamage += 12;
    
    for(auto& attack : attacks) {
        if(attack->getTag() == "Ballistic") {
            attack->setDamage(10); 
            attack->setCooldown(0.5f);
        }
    }
    
    skill->setCooldown(45.0f); 
    skill->setTimer(skill->getCooldownTime() - 5.0f); // Set the timer to 20 seconds less than the cooldown
}

std::unique_ptr<Upgrade> PreEmptiveStrike::buy() {
    return nextUpgrade->clone();
}