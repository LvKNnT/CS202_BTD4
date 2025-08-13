#include "EnhancedEyesight.h"
#include "../../../../core/Game.h"

#include "CrossBow.h"

EnhancedEyesight::EnhancedEyesight() 
    : Upgrade("Enhanced Eyesight", 200, "Shoots even further and can detect Camo bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<CrossBow>(); // Temporary lmao
    tag = "Enhanced Eyesight";
}

EnhancedEyesight::EnhancedEyesight(const EnhancedEyesight& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> EnhancedEyesight::clone() const {
    return std::make_unique<EnhancedEyesight>(*this);
}

void EnhancedEyesight::loadTexture() {
    // Load the texture for Enhanced Eyesight upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/EnhancedEyesightUpgradeIcon.png");
}

void EnhancedEyesight::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 32;
    attackBuff.lifeSpanRatio *= 1.6f / 1.35f; 
    attackBuff.speed += 100;
    attackBuff.properties.canCamo = true;
    attackBuff.extraNormalDebuff += BloonDebuff().getIKnockBack(0.0f, 1.5f);
    attackBuff.extraMoabDebuff += BloonDebuff().getIKnockBack(0.0f, 0.75f);
}

std::unique_ptr<Upgrade> EnhancedEyesight::buy() {
    return nextUpgrade->clone();
}
