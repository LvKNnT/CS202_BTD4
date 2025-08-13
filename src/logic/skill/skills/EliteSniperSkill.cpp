#include "EliteSniperSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

EliteSniperSkill::EliteSniperSkill()
    : Skill(60.0f, "Elite Sniper") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> EliteSniperSkill::clone() const {
    return std::make_unique<EliteSniperSkill>(*this);
}

void EliteSniperSkill::loadTexture() {
    // Load the texture for the Elite Sniper skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Sniper_Monkey/EliteSniperUpgradeIcon.png");
}

void EliteSniperSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool EliteSniperSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float EliteSniperSkill::getCooldown() const {
    return cooldown;
}

void EliteSniperSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    // Create an elite sniper attack at the tower's position
    // Here you can implement the logic to create an elite sniper effect or item
    resourceManager.getResource().cash += 3000; 

    // Reset the timer after activation
    timer = 0.0f;
}

void EliteSniperSkill::inActivateSkill() {
    // Reset the skill state if needed
    timer = cooldown; // Reset the timer to cooldown
    std::cout << "Elite Sniper skill deactivated." << std::endl;
}