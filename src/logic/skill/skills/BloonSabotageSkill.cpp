#include "BloonSabotageSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

BloonSabotageSkill::BloonSabotageSkill()
    : Skill(60.0f, "Bloon Sabotage") {
    // Instant cooldown
    duration = 15.0f;
    timer = cooldown;
}

std::unique_ptr<Skill> BloonSabotageSkill::clone() const {
    return std::make_unique<BloonSabotageSkill>(*this);
}

void BloonSabotageSkill::loadTexture() {
    // Load the texture for the Bloon Sabotage Skillsp skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Ninja_Monkey/BloonSabotageUpgradeIcon.png");
}

void BloonSabotageSkill::update() {
    // Update the skill timer
    if (timer < cooldown || timer < duration) {
        timer += GetFrameTime();
    }
    if(timer > duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
    }
}

bool BloonSabotageSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown && timer >= duration;
}

float BloonSabotageSkill::getCooldown() const {
    return cooldown;
}

void BloonSabotageSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    for(auto &enemy:enemies) {
        if(SkillFriendAccess::getEnemyType(*enemy) == BloonType::Bad) continue;
        enemy->setDebuff(BloonDebuff().getISlow(0.5f, 15), BloonDebuff().getISlow(0.5f, 15));
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

    for (size_t i = 0; i < std::min<size_t>(1, towerDistances.size()); ++i) {
        if (auto towerPtr = towerDistances[i].second.lock()) {
            closestTowers.push_back(towerPtr);
        }
    }

    // Buff the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getTag(*towerPtr) = "Bloon Sabotage Ninja"; // Change the tag to Bloon Sabotage Ninja
            break;
        }
    }

    // Reset the skill timer after activation
    timer = 0.0f;

    std::cerr << "Activated Bloon Sabotage skill for " << closestTowers.size() << " towers." << std::endl;
}

void BloonSabotageSkill::inActivateSkill() {
    if(timer < duration) return; // Only deactivate if the skill is still active
    if(closestTowers.empty()) return; // No towers to deactivate

    
    // Reset the attack buffs of the closest towers
    for (auto& t : closestTowers) {
        if (auto towerPtr = t.lock()) {
            SkillFriendAccess::getTag(*towerPtr) = "NinjaMonkey"; // Reset the tag to Ninja Monkey
            break;
        }
    }

    closestTowers.clear(); // Clear the list of closest towers

    std::cerr << "Deactivated Bloon Sabotage skill." << std::endl;
}