#include "SharpShots.h"

SharpShots::SharpShots() 
    : Upgrade("Sharp Shots", 140, "Can pop 1 extra Bloon per shot.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "SharpShots";
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
    texture = Game::Instance().getTextureManager().getTexture(tag);
}

void SharpShots::draw() const {
    // Currently only log
    std::cerr << "Draw SharpShots\n";
}

void SharpShots::update(std::vector<std::unique_ptr<Attack> >& attacks) {
    for(auto& attack : attacks) {
        // Increase the pierce of each dart attack by 1
        attack->setPierce(attack->getPierce() + 1);
    }
}

std::unique_ptr<Upgrade> SharpShots::buy() {
    return nextUpgrade->clone();
}