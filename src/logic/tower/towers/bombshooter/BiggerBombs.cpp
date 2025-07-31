#include "BiggerBombs.h"
#include "../../../../core/Game.h"


BiggerBombs::BiggerBombs() 
    : Upgrade("Bigger Bombs", 250, "Shoots larger bombs, they have a larger blast area and more popping power.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Bigger Bombs";
}

BiggerBombs::BiggerBombs(const BiggerBombs& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BiggerBombs::clone() const {
    return std::make_unique<BiggerBombs>(*this);
}

void BiggerBombs::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/BiggerBombsUpgradeIcon.png");
}

void BiggerBombs::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for(auto& attack : attacks) {
        attackBuff.range += 6.0f; // Increase range by 6
        attackBuff.pierce += 6;
    }
}

std::unique_ptr<Upgrade> BiggerBombs::buy() {
    return nextUpgrade->clone();
}