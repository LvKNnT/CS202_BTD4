#include "AbsoluteZeroSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

AbsoluteZeroSkill::AbsoluteZeroSkill()
    : Skill(20.0f, "Absolute Zero Skill"), iceSkill("Freeze") {
    // Instant cooldown
    duration = 10.0f;
    timer = cooldown;
}

std::unique_ptr<Skill> AbsoluteZeroSkill::clone() const {
    return std::make_unique<AbsoluteZeroSkill>(*this);
}

void AbsoluteZeroSkill::loadTexture() {
    // Load the texture for the Elite Sniper Passive skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Ice_Monkey/AbsoluteZeroUpgradeIcon.png");
}

void AbsoluteZeroSkill::update() {
    // Update the skill timer
    if (timer < cooldown || timer < duration) {
        timer += GetFrameTime();
    }
    if(timer >= duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
    }
}

bool AbsoluteZeroSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown && timer >= duration;
}

float AbsoluteZeroSkill::getCooldown() const {
    return cooldown;
}

void AbsoluteZeroSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    for (auto& enemy : enemies) {
        if (enemy) {
            enemy->setDebuff(BloonDebuff().getIFreeze(duration), BloonDebuff().getIFreeze(duration));
        }
    }

    for(auto& tower : towers) {
        if (!tower) continue;

        if(SkillFriendAccess::getTowerType(*tower) == TowerType::IceMonkey) {
            SkillFriendAccess::getAttackBuff(*tower).cooldownRatio *= 0.5f; // Halve the attack speed
            affectedTowers.push_back(tower); // Store the affected tower
        }
    }

    std::cerr << "Absolute Zero Skill activated for " << duration << " seconds." << std::endl;

    // Reset the timer after activation
    iceSkill.start();
    timer = 0.0f;
}

void AbsoluteZeroSkill::inActivateSkill() {
    if(affectedTowers.empty()) return; // No towers to deactivate

    for(auto& tower : affectedTowers) {
        if (auto towerPtr = tower.lock()) {
            SkillFriendAccess::getAttackBuff(*towerPtr).cooldownRatio /= 0.5f; // Reset the attack speed
        }
    }
    iceSkill.stop();

    affectedTowers.clear(); // Clear the affected towers
    std::cerr << "Absolute Zero Skill deactivated." << std::endl;
}

