#include "FasterReload.h"
#include "../../../../core/Game.h"

#include "MissileLauncher.h"

FasterReload::FasterReload() 
    : Upgrade("Faster Reload", 250, "Reloads faster.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MissileLauncher>(); // Temporary lmao
    tag = "Faster Reload";
}

FasterReload::FasterReload(const FasterReload& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FasterReload::clone() const {
    return std::make_unique<FasterReload>(*this);
}

void FasterReload::loadTexture() {
    // Load the texture for Faster Reload upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/FasterReloadUpgradeIcon.png");
}

void FasterReload::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    attackBuff.cooldownRatio *= 0.75f; // Reduce cooldown by 25%
}

std::unique_ptr<Upgrade> FasterReload::buy() {
    return nextUpgrade->clone();
}