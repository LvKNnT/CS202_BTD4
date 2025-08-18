#include "FirstStrikeCapabilitySkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

FirstStrikeCapabilitySkill::FirstStrikeCapabilitySkill()
    : Skill(60.0f, "First Strike Capability") {
    // Instant cooldown
    timer = cooldown - 20.0f;
}

std::unique_ptr<Skill> FirstStrikeCapabilitySkill::clone() const {
    return std::make_unique<FirstStrikeCapabilitySkill>(*this);
}

void FirstStrikeCapabilitySkill::loadTexture() {
    // Load the texture for the MOAB Assassin skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Monkey_Sub/FirstStrikeCapabilityUpgradeIcon.png");
}

void FirstStrikeCapabilitySkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool FirstStrikeCapabilitySkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float FirstStrikeCapabilitySkill::getCooldown() const {
    return cooldown;
}

void FirstStrikeCapabilitySkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    std::cerr << "Activating First Strike Capability skill for tower ID: " << SkillFriendAccess::getTowerId(*tower) << std::endl;

    Vector2 position = SkillFriendAccess::getTowerPosition(*tower);

    // Find all the MOAB-Class bloons in the enemies list
    std::vector<Enemy*> moabEnemies;
    for (const auto& enemy : enemies) {
        moabEnemies.push_back(enemy.get());
    }

    // Pick one enemy based on the tower's target priority
    // Sadly have to use switch/case here.
    Enemy* targetEnemy = nullptr;
    if(!moabEnemies.empty()) {
        switch(SkillFriendAccess::getTargetPriority(*tower)) {
            case TargetPriority::First:
            targetEnemy = moabEnemies.front();
            break;
            case TargetPriority::Last:
            targetEnemy = moabEnemies.back();
            break;
            case TargetPriority::Close:
            targetEnemy = *std::min_element(moabEnemies.begin(), moabEnemies.end(),
                [&](Enemy* a, Enemy* b) {
                    return Vector2Distance(SkillFriendAccess::getEnemyPosition(*a), SkillFriendAccess::getTowerPosition(*tower))
                         < Vector2Distance(SkillFriendAccess::getEnemyPosition(*b), SkillFriendAccess::getTowerPosition(*tower));
                });
            break;
            case TargetPriority::Strong:
            targetEnemy = *std::max_element(moabEnemies.begin(), moabEnemies.end(),
            [&](Enemy* a, Enemy* b) {
                return SkillFriendAccess::getLivesLost(*a) < SkillFriendAccess::getLivesLost(*b); // Compare health
            });
            break;
        }
    }

    // If a target enemy is found, apply the MOAB Assassin effect
    if (targetEnemy) {
        BulletProperties properties = {true, false, true, true, false, true}; // MOAB Assassin can hit all bloon types
        properties = properties.getITracing(1000.0f, SkillFriendAccess::getTargetPriority(*tower), true);

        float angle = atan2f(SkillFriendAccess::getEnemyPosition(*targetEnemy).y - SkillFriendAccess::getTowerPosition(*tower).y, SkillFriendAccess::getEnemyPosition(*targetEnemy).x - SkillFriendAccess::getTowerPosition(*tower).x);
        SkillFriendAccess::getTowerRotation(*tower) = angle * (180.0f / PI) + 90.0f; // Convert radians to degrees
        float rotation = angle * (180.0f / PI); // Convert radians to degrees

        bulletManager.spawnBullet(BulletType::Ballistic, position, 
            Vector2Add({45.0f, 15.0f}, SkillFriendAccess::getAttackBuff(*tower).size),
            rotation,
            - 10000 - SkillFriendAccess::getAttackBuff(*tower).damage,
            1000 * SkillFriendAccess::getAttackBuff(*tower).speedRatio + SkillFriendAccess::getAttackBuff(*tower).speed,
            80 * SkillFriendAccess::getAttackBuff(*tower).pierceRatio + SkillFriendAccess::getAttackBuff(*tower).pierce,
            1000 * SkillFriendAccess::getAttackBuff(*tower).lifeSpanRatio, 
            properties,
            SkillFriendAccess::getAttackBuff(*tower).extraNormalDebuff,
            SkillFriendAccess::getAttackBuff(*tower).extraMoabDebuff,
            SkillFriendAccess::getAttackBuff(*tower),
            SkillFriendAccess::getTowerId(*tower));

        // Log the activation
        std::cerr << "First Strike Capability skill activated to target enemy with ID: " << SkillFriendAccess::getEnemyId(*targetEnemy) << std::endl;
    }

    timer = 0.0f; // Reset the timer after activation
}

void FirstStrikeCapabilitySkill::inActivateSkill() {
    // do nothin
}