#include "GrandSaboteurSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

GrandSaboteurSkill::GrandSaboteurSkill()
    : Skill(60.0f, "Grand Saboteur") {
    // Instant cooldown
    duration = 30.0f;
    timer = 0;
    isSkillActivating = true;
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
    timer += GetFrameTime();
    if(isSkillActivating && timer >= duration) {
        inActivateSkill(); // Deactivate the skill if the duration has passed
        timer = 0;
        isSkillActivating = false;
    } 
    if(!isSkillActivating && timer >= cooldown) {
        timer = 0;
        isSkillActivating = true;
    }
}

bool GrandSaboteurSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    if(isSkillActivating && timer < duration) return true;
    if(!isSkillActivating && timer >= cooldown) return true;
    return false;
}

float GrandSaboteurSkill::getCooldown() const {
    return cooldown;
}

void GrandSaboteurSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    for(auto &enemy:enemies) {
        // MOAB class
        if(SkillFriendAccess::getEnemyType(*enemy) >= BloonType::Moab && !affectedEnemies[SkillFriendAccess::getEnemyId(*enemy)]) {
            SkillFriendAccess::getEnemyHealth(*enemy) *= 0.75;
            affectedEnemies[SkillFriendAccess::getEnemyId(*enemy)] = 1;
        }
        enemy->setDebuff(BloonDebuff().getISlow(0.5f, duration - timer), BloonDebuff().getISlow(0.5f, duration - timer));
    }

    // Buff all Ninja towers
    for (auto& towerPtr : towers) {
        if(SkillFriendAccess::getTowerType(*towerPtr) != TowerType::NinjaMonkey || affectedTowers.count(SkillFriendAccess::getTowerId(*towerPtr))) continue;
        SkillFriendAccess::getAttackBuff(*towerPtr).range += 10; 
        SkillFriendAccess::getAttackBuff(*towerPtr).extraMoabDebuff.bonusDamage += 2;
        SkillFriendAccess::getTag(*towerPtr) = "Grand Saboteur Ninja"; // Change the tag to Grand Saboteur Ninja
        affectedTowers[SkillFriendAccess::getTowerId(*towerPtr)] = towerPtr;
    }

    if(timer == 0.0f) std::cerr << "Activated Grand Saboteur skill for " << affectedTowers.size() << " towers. (maybe more if they are added)" << std::endl;
}

void GrandSaboteurSkill::inActivateSkill() {
    if(timer < duration) return; // Only deactivate if the skill is still active

    // Reset the attack buffs of the closest towers
    for (auto& [id, towerPtr] : affectedTowers) {
        SkillFriendAccess::getAttackBuff(*towerPtr).range -= 10;
        SkillFriendAccess::getAttackBuff(*towerPtr).extraMoabDebuff.bonusDamage -= 2;
        SkillFriendAccess::getTag(*towerPtr) = "NinjaMonkey"; // Reset the tag to Ninja Monkey
    }

    std::cerr << "Deactivated Grand Saboteur skill." << std::endl;
    affectedEnemies.clear();
    affectedTowers.clear();
}