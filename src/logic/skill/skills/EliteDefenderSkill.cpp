#include "EliteDefenderSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

EliteDefenderSkill::EliteDefenderSkill()
    : Skill(10.0f, "Elite Defender") {
    // Instant cooldown
    duration = 7.0f; // Set the duration for the skill
    timer = cooldown;
}

std::unique_ptr<Skill> EliteDefenderSkill::clone() const {
    return std::make_unique<EliteDefenderSkill>(*this);
}

void EliteDefenderSkill::loadTexture() {
    // Load the texture for the Elite Defender skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Sniper_Monkey/EliteDefenderUpgradeIcon.png");
}

void EliteDefenderSkill::update() {
    // Update the skill timer
    if (timer < cooldown || timer < duration) {
        timer += GetFrameTime();
    }
    if(timer > duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
    }
}

bool EliteDefenderSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown && timer >= duration;
}

float EliteDefenderSkill::getCooldown() const {
    return cooldown;
}

void EliteDefenderSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;
    if (currentHealth <= resourceManager.getResource().lives) {
        // no need to activate skill if there is no lives lost
        currentHealth = resourceManager.getResource().lives; 
        return; 
    }

    towerPtr = tower;
    SkillFriendAccess::getAttackBuff(*tower).cooldownRatio *= 0.25;

    // Reset the timer after activation
    timer = 0.0f;
}

void EliteDefenderSkill::inActivateSkill() {
    if(auto tower = towerPtr.lock()) {
        SkillFriendAccess::getAttackBuff(*tower).cooldownRatio /= 0.25; // Reset the cooldown ratio
    }

    // Reset the skill state if needed
    timer = cooldown; // Reset the timer to cooldown
}