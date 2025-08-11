#include "PlasmaMonkeyFanClubSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

PlasmaMonkeyFanClubSkill::PlasmaMonkeyFanClubSkill()
    : Skill(50.0f, "Plasma Monkey Fan Club") {
    // Instant cooldown
    duration = 15.0f;
    timer = cooldown;
}

std::unique_ptr<Skill> PlasmaMonkeyFanClubSkill::clone() const {
    return std::make_unique<PlasmaMonkeyFanClubSkill>(*this);
}

void PlasmaMonkeyFanClubSkill::loadTexture() {
    // Load the texture for the Plasma Monkey Fan Club skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Dart_Monkey/PMFCUpgradeIcon.png");
}

void PlasmaMonkeyFanClubSkill::update() {
    // Update the skill timer
    if (timer < cooldown || timer < duration) {
        timer += GetFrameTime();
    }
    if(timer > duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
    }
}

bool PlasmaMonkeyFanClubSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown && timer >= duration;
}

float PlasmaMonkeyFanClubSkill::getCooldown() const {
    return cooldown;
}

void PlasmaMonkeyFanClubSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    Vector2 position = SkillFriendAccess::getTowerPosition(*tower);

    // Find 20 towers closest to position
    std::vector<std::pair<float, std::weak_ptr<Tower>>> towerDistances;
    for (auto& t : towers) {
        if(SkillFriendAccess::getTowerType(*t) != TowerType::DartMonkey) continue; // Only activate for Dart Monkeys

        float dist = Vector2Distance(SkillFriendAccess::getTowerPosition(*t), position);
        towerDistances.emplace_back(dist, std::weak_ptr<Tower>(t));
    }

    std::sort(towerDistances.begin(), towerDistances.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    // Activate the closest 20 towers
    for (size_t i = 0; i < std::min(towerDistances.size(), size_t(20)); ++i) {
        if (auto towerPtr = towerDistances[i].second.lock()) {
            closestTowers.push_back(towerPtr);
        }
    }

    // Buff the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getAttackBuff(*towerPtr).range += 32.0f;
            SkillFriendAccess::getAttackBuff(*towerPtr).cooldownRatio *= 0.06f; 
            SkillFriendAccess::getAttackBuff(*towerPtr).damage += 1;
            SkillFriendAccess::getAttackBuff(*towerPtr).pierce += 3; 
            SkillFriendAccess::getTag(*towerPtr) = "Plasma Monkey Fan Club Dart"; // Change the tag to Plasma Monkey Fan Club Dart
        }
    }

    // Reset the timer after activation
    timer = 0.0f;

    std::cerr << "Activated Plasma Monkey Fan Club skill for " << closestTowers.size() << " towers." << std::endl;
}

void PlasmaMonkeyFanClubSkill::inActivateSkill() {
    if(timer < duration) return;
    if (closestTowers.empty()) return; 

    // Deactivate the skill for all activated towers
    for (auto& towerWeakPtr : closestTowers) {
        if (auto tower = towerWeakPtr.lock()) {
            SkillFriendAccess::getAttackBuff(*tower).range -= 32.0f;
            SkillFriendAccess::getAttackBuff(*tower).cooldownRatio /= 0.06f; 
            SkillFriendAccess::getAttackBuff(*tower).damage -= 1; 
            SkillFriendAccess::getAttackBuff(*tower).pierce -= 3; 
            SkillFriendAccess::getTag(*tower) = "DartMonkey"; // Reset the tag to Dart Monkey
        }
    }
    closestTowers.clear(); // Clear the list of activated towers

    std::cerr << "Deactivated Plasma Monkey Fan Club skill." << std::endl;
}