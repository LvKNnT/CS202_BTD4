#include "EnhancedFreeze.h"
#include "../../../../core/Game.h"

#include "DeepFreeze.h"

EnhancedFreeze::EnhancedFreeze() 
    : Upgrade("Enhanced Freeze", 200, "Attacks faster and freezes for longer.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<DeepFreeze>(); // Temporary lmao
    tag = "Enhanced Freeze";
}

EnhancedFreeze::EnhancedFreeze(const EnhancedFreeze& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> EnhancedFreeze::clone() const {
    return std::make_unique<EnhancedFreeze>(*this);
}

void EnhancedFreeze::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/EnhancedFreezeUpgradeIcon.png");
}

void EnhancedFreeze::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *- 2.0f / 3.0f;
    attackBuff.extraNormalDebuff += BloonDebuff().getIFreeze(1.75f);
}

std::unique_ptr<Upgrade> EnhancedFreeze::buy() {
    return nextUpgrade->clone();
}