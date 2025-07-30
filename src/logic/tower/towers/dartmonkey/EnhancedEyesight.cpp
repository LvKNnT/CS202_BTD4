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

void EnhancedEyesight::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for (auto& attack : attacks) {
        attackBuff.range += 32;
        attackBuff.lifeSpanRatio *= 1.2f / 1.15f; 
        attackBuff.speedRatio *= 1.1f;
        attackBuff.properties.canCamo = true;
    }
}

std::unique_ptr<Upgrade> EnhancedEyesight::buy() {
    return nextUpgrade->clone();
}
