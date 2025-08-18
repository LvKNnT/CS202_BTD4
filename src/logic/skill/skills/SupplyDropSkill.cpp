#include "SupplyDropSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

SupplyDropSkill::SupplyDropSkill()
    : Skill(90.0f, "Supply Drop") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> SupplyDropSkill::clone() const {
    return std::make_unique<SupplyDropSkill>(*this);
}

void SupplyDropSkill::loadTexture() {
    // Load the texture for the Supply Drop skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Dart_Monkey/CashDropUpgradeIcon.png");
}

void SupplyDropSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool SupplyDropSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float SupplyDropSkill::getCooldown() const {
    return cooldown;
}

void SupplyDropSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    // Create a supply drop at the tower's position
    // Here you can implement the logic to create a supply drop effect or item
    resourceManager.getResource().cash += 1100;

    // Reset the timer after activation
    timer = 0.0f;
    MySound skillSound("ActivateSkill");
    skillSound.start();
}

void SupplyDropSkill::inActivateSkill() {
    // Reset the skill state if needed
    timer = cooldown; // Reset the timer to cooldown
    std::cout << "Supply Drop skill deactivated." << std::endl;
}