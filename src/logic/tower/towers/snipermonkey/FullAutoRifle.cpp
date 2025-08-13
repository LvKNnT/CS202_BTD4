#include "FullAutoRifle.h"
#include "../../../../core/Game.h"

#include "EliteDefender.h"

FullAutoRifle::FullAutoRifle() 
    : Upgrade("Full Auto Rifle", 4100, "Fully automatic weapon with incredible popping power.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<EliteDefender>(); // No further upgrade available
    tag = "Full Auto Rifle";
}

FullAutoRifle::FullAutoRifle(const FullAutoRifle& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FullAutoRifle::clone() const {
    return std::make_unique<FullAutoRifle>(*this);
}

void FullAutoRifle::loadTexture() {
    // Load the texture for Full Auto Rifle upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/FullAutoRifleUpgradeIcon.png");
}

void FullAutoRifle::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.5f; // Halve the cooldown for full auto rifle
    attackBuff.extraMoabDebuff.bonusDamage += 2;
}

std::unique_ptr<Upgrade> FullAutoRifle::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}