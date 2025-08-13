#include "BombBliztSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

BombBliztSkill::BombBliztSkill()
    : Skill(90.0f, "Bomb Blitz") {
    // Instant cooldown
    timer = cooldown;
}

BombBliztSkill::BombBliztSkill(ResourceManager& resourceManager)
    : Skill(90.0f, "Bomb Blitz") {
    timer = cooldown; // Initialize timer to cooldown

    currentHealth = resourceManager.getResource().lives; // Initialize current health from resource manager
}

std::unique_ptr<Skill> BombBliztSkill::clone() const {
    return std::make_unique<BombBliztSkill>(*this);
}

void BombBliztSkill::loadTexture() {
    // Load the texture for the Bomb Blitz skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Bomb_Shooter/BombBlitzUpgradeIcon.png");
}

void BombBliztSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool BombBliztSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float BombBliztSkill::getCooldown() const {
    return cooldown;
}

void BombBliztSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;
    if (currentHealth <= resourceManager.getResource().lives) {
        // no need to activate skill if there is no lives lost
        currentHealth = resourceManager.getResource().lives; 
        return; 
    }

    // std::cerr << "Activating Bomb Blitz skill for tower ID: " << SkillFriendAccess::getTowerId(*tower) << std::endl;

    // delete all enemies that below BFBs
    for(auto it = enemies.begin(); it != enemies.end();) {
        if (SkillFriendAccess::getType(**it) < BloonType::Bfb) {
            it = enemies.erase(it); // Remove the bloon from the list
        } else {
            ++it; // Move to the next bloon
        }
    }

    timer = 0.0f; // Reset the timer after activation
    currentHealth = resourceManager.getResource().lives; // Reset current health to the current lives
}

void BombBliztSkill::inActivateSkill() {
    // do nothin
}