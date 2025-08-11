#include "GrandSaboteurSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

GrandSaboteurSkill::GrandSaboteurSkill()
    : Skill(60.0f, "Grand Saboteur") {
    // Instant cooldown
    duration = 30.0f;
    timer = cooldown;
}

std::unique_ptr<Skill> GrandSaboteurSkill::clone() const {
    return std::make_unique<GrandSaboteurSkill>(*this);
}

void GrandSaboteurSkill::loadTexture() {
    // Load the texture for the Bloon Sabotage Skillsp skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Ninja_Monkey/GrandSaboteurUpgradeIcon.png");
}

void GrandSaboteurSkill::update() {
    // Update the skill timer
    if (timer < cooldown || timer < duration) {
        timer += GetFrameTime();
    }
    if(timer > duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
    }
}

bool GrandSaboteurSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown && timer >= duration;
}

float GrandSaboteurSkill::getCooldown() const {
    return cooldown;
}

void GrandSaboteurSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    for(auto &enemy:enemies) {
        // MOAB class
        if(SkillFriendAccess::getEnemyType(*enemy) == BloonType::Moab 
        || SkillFriendAccess::getEnemyType(*enemy) == BloonType::Bfb 
        || SkillFriendAccess::getEnemyType(*enemy) == BloonType::Zomg
        || SkillFriendAccess::getEnemyType(*enemy) == BloonType::Ddt
        || SkillFriendAccess::getEnemyType(*enemy) == BloonType::Bad) {
            SkillFriendAccess::getEnemyHealth(*enemy) *= 0.75;
        }
        enemy->setDebuff(BloonDebuff().getISlow(0.5f, 30), BloonDebuff().getISlow(0.5f, 30));
    }

    Vector2 position = SkillFriendAccess::getTowerPosition(*tower);

    // Find 10 towers closest to position
    std::vector<std::pair<float, std::weak_ptr<Tower>>> towerDistances;
    for (auto& t : towers) {
        if(SkillFriendAccess::getTowerType(*t) != TowerType::NinjaMonkey) continue; // Only activate for Dart Monkeys

        float dist = Vector2Distance(SkillFriendAccess::getTowerPosition(*t), position);
        towerDistances.emplace_back(dist, std::weak_ptr<Tower>(t));
    }

    std::sort(towerDistances.begin(), towerDistances.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    for (size_t i = 0; i < towerDistances.size(); ++i) {
        if (auto towerPtr = towerDistances[i].second.lock()) {
            closestTowers.push_back(towerPtr);
        }
    }

    // Buff the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getAttackBuff(*towerPtr).range += 10; 
            SkillFriendAccess::getAttackBuff(*towerPtr).extraMoabDebuff.bonusDamage += 2;
            SkillFriendAccess::getTag(*towerPtr) = "Grand Saboteur Ninja"; // Change the tag to Super Monkey Fan Club Dart
        }
    }

    // Reset the skill timer after activation
    timer = 0.0f;

    std::cerr << "Activated Grand Saboteur skill for " << closestTowers.size() << " towers." << std::endl;
}

void GrandSaboteurSkill::inActivateSkill() {
    if(timer < duration) return; // Only deactivate if the skill is still active
    if(closestTowers.empty()) return; // No towers to deactivate

    // Reset the attack buffs of the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getAttackBuff(*towerPtr).range -= 10;
            SkillFriendAccess::getAttackBuff(*towerPtr).extraMoabDebuff.bonusDamage -= 2;
            SkillFriendAccess::getTag(*towerPtr) = "NinjaMonkey"; // Reset the tag to Ninja Monkey
        }
    }

    closestTowers.clear(); // Clear the list of closest towers

    std::cerr << "Deactivated Grand Saboteur skill." << std::endl;
}