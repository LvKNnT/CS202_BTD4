#include "BiggerBombs.h"
#include "../../../../core/Game.h"
#include "raymath.h"

#include "HeavyBombs.h"

BiggerBombs::BiggerBombs() 
    : Upgrade("Bigger Bombs", 250, "Shoots larger bombs, they have a larger blast area and more popping power.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<HeavyBombs>(); // Temporary lmao
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
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/BiggerBombsUpgradeIcon.png");
}

void BiggerBombs::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.size = Vector2Add(attackBuff.size, {10.0f, 10.0f});
    attackBuff.pierce += 6;
}

std::unique_ptr<Upgrade> BiggerBombs::buy() {
    return nextUpgrade->clone();
}