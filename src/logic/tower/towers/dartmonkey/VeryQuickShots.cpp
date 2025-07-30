#include "VeryQuickShots.h"
#include "../../../../core/Game.h"

#include "TripleShot.h"

VeryQuickShots::VeryQuickShots() 
    : Upgrade("Very Quick Shots", 190, "Shoots 33% faster.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<TripleShot>(); // Temporary lmao
    tag = "Very Quick Shots";
}

VeryQuickShots::VeryQuickShots(const VeryQuickShots& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> VeryQuickShots::clone() const {
    return std::make_unique<VeryQuickShots>(*this);
}

void VeryQuickShots::loadTexture() {
    // Load the texture for Very Quick Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/VeryQuickShotsUpgradeIcon.png");
}

void VeryQuickShots::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for (auto& attack : attacks) {
        attackBuff.cooldownRatio *= 0.8f; // Reduce cooldown by 30%
    }
}

std::unique_ptr<Upgrade> VeryQuickShots::buy() {
    return nextUpgrade->clone();
}