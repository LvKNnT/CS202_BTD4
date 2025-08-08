#include "SharpShots.h"
#include "../../../../core/Game.h"

#include "RazorSharpShots.h"

SharpShots::SharpShots() 
    : Upgrade("Sharp Shots", 140, "Can pop 1 extra Bloon per shot.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<RazorSharpShots>(); // Temporary lmao
    tag = "Sharp Shots";
}

SharpShots::SharpShots(const SharpShots& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SharpShots::clone() const {
    return std::make_unique<SharpShots>(*this);
}

void SharpShots::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/SharpShotsUpgradeIcon.png");
}

void SharpShots::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.pierceRatio *= 2.0f;
}

std::unique_ptr<Upgrade> SharpShots::buy() {
    return nextUpgrade->clone();
}