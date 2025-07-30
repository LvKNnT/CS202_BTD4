#include "RazorSharpShots.h"
#include "../../../../core/Game.h"

#include "SpikeOPult.h"

RazorSharpShots::RazorSharpShots() 
    : Upgrade("Razor Sharp Shots", 200, "Can pop 2 more bloons per shot.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SpikeOPult>(); 
    tag = "Razor Sharp Shots";
}

RazorSharpShots::RazorSharpShots(const RazorSharpShots& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> RazorSharpShots::clone() const {
    return std::make_unique<RazorSharpShots>(*this);
}

void RazorSharpShots::loadTexture() {
    // Load the texture for Razor Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/RazorSharpShotsUpgradeIcon.png");
}

void RazorSharpShots::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for (auto& attack : attacks) {
        attackBuff.pierce += 1;
    }
}

std::unique_ptr<Upgrade> RazorSharpShots::buy() {
    return nextUpgrade->clone();
}