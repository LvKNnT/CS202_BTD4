#include "SuperMonkeyFanClubSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

SuperMonkeyFanClubSkill::SuperMonkeyFanClubSkill()
    : Skill(50.0f, "Super Monkey Fan Club") {
    // Instant cooldown
    duration = 15.0f;
    timer = cooldown;
}

std::unique_ptr<Skill> SuperMonkeyFanClubSkill::clone() const {
    return std::make_unique<SuperMonkeyFanClubSkill>(*this);
}

void SuperMonkeyFanClubSkill::loadTexture() {
    // Load the texture for the Super Monkey Fan Club skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Dart_Monkey/SuperMonkeyFanClubUpgradeIcon.png");
}

void SuperMonkeyFanClubSkill::update() {
    // Update the skill timer
    if (timer < cooldown || timer < duration) {
        timer += GetFrameTime();
    }
    if(timer > duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
    }
}

bool SuperMonkeyFanClubSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown && timer >= duration;
}

float SuperMonkeyFanClubSkill::getCooldown() const {
    return cooldown;
}

void SuperMonkeyFanClubSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    Vector2 position = SkillFriendAccess::getTowerPosition(*tower);

    // Find 10 towers closest to position
    std::vector<std::pair<float, std::weak_ptr<Tower>>> towerDistances;
    for (auto& t : towers) {
        if(SkillFriendAccess::getTowerType(*t) != TowerType::DartMonkey) continue; // Only activate for Dart Monkeys

        float dist = Vector2Distance(SkillFriendAccess::getTowerPosition(*t), position);
        towerDistances.emplace_back(dist, std::weak_ptr<Tower>(t));
    }

    std::sort(towerDistances.begin(), towerDistances.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    for (size_t i = 0; i < std::min<size_t>(10, towerDistances.size()); ++i) {
        if (auto towerPtr = towerDistances[i].second.lock()) {
            closestTowers.push_back(towerPtr);
        }
    }

    // Buff the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getAttackBuff(*towerPtr).cooldownRatio *= 0.25f; // Halve the cooldown
            SkillFriendAccess::getAttackBuff(*towerPtr).range += 32.0f;
            SkillFriendAccess::getTag(*towerPtr) = "Super Monkey Fan Club Dart"; // Change the tag to Super Monkey Fan Club Dart
        }
    }

    // Reset the skill timer after activation
    timer = 0.0f;

    std::cerr << "Activated Super Monkey Fan Club skill for " << closestTowers.size() << " towers." << std::endl;
}

void SuperMonkeyFanClubSkill::inActivateSkill() {
    if(timer < duration) return; // Only deactivate if the skill is still active
    if(closestTowers.empty()) return; // No towers to deactivate

    // Reset the attack buffs of the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getAttackBuff(*towerPtr).cooldownRatio /= 0.25f; // Reset to normal cooldown
            SkillFriendAccess::getAttackBuff(*towerPtr).range -= 32.0f; // Reset range
            SkillFriendAccess::getTag(*towerPtr) = "DartMonkey"; // Reset the tag to Dart Monkey
        }
    }

    closestTowers.clear(); // Clear the list of closest towers

    std::cerr << "Deactivated Super Monkey Fan Club skill." << std::endl;
}