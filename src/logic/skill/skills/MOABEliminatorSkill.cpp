#include "MOABEliminatorSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

MOABEliminatorSkill::MOABEliminatorSkill()
    : Skill(10.0f, "MOAB Eliminator") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> MOABEliminatorSkill::clone() const {
    return std::make_unique<MOABEliminatorSkill>(*this);
}

void MOABEliminatorSkill::loadTexture() {
    // Load the texture for the MOAB Eliminator skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Bomb_Shooter/MOABEliminatorUpgradeIcon.png");
}

void MOABEliminatorSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool MOABEliminatorSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float MOABEliminatorSkill::getCooldown() const {
    return cooldown;
}

void MOABEliminatorSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    // std::cerr << "Activating MOAB Assassin skill for tower ID: " << SkillFriendAccess::getTowerId(*tower) << std::endl;

    Vector2 position = SkillFriendAccess::getTowerPosition(*tower);

    // Find all the MOAB-Class bloons in the enemies list
    std::vector<Enemy*> moabEnemies;
    for (const auto& enemy : enemies) {
        if (SkillFriendAccess::getType(*enemy) >= BloonType::Moab) { // Check if the enemy is a MOAB-Class bloon
            moabEnemies.push_back(enemy.get());
        }
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
        BulletProperties properties = {true, true, true, true, false, true}; // MOAB Assassin can hit all bloon types

        float angle = atan2f(SkillFriendAccess::getEnemyPosition(*targetEnemy).y - SkillFriendAccess::getTowerPosition(*tower).y, SkillFriendAccess::getEnemyPosition(*targetEnemy).x - SkillFriendAccess::getTowerPosition(*tower).x);
        SkillFriendAccess::getTowerRotation(*tower) = angle * (180.0f / PI) + 90.0f; // Convert radians to degrees
        float rotation = angle * (180.0f / PI); // Convert radians to degrees

        bulletManager.spawnBullet(BulletType::MOABAssassin, position, 
            Vector2Add({40.0f, 40.0f}, SkillFriendAccess::getAttackBuff(*tower).size),
            rotation,
            4500 + SkillFriendAccess::getAttackBuff(*tower).damage,
            1000 * SkillFriendAccess::getAttackBuff(*tower).speedRatio + SkillFriendAccess::getAttackBuff(*tower).speed,
            100 * SkillFriendAccess::getAttackBuff(*tower).pierceRatio + SkillFriendAccess::getAttackBuff(*tower).pierce,
            1000 * SkillFriendAccess::getAttackBuff(*tower).lifeSpanRatio, 
            properties,
            SkillFriendAccess::getAttackBuff(*tower).extraNormalDebuff,
            SkillFriendAccess::getAttackBuff(*tower).extraMoabDebuff,
            SkillFriendAccess::getAttackBuff(*tower),
            SkillFriendAccess::getTowerId(*tower));

        // Log the activation
        // std::cerr << "Activated MOAB Assassin skill on enemy ID: " << targetEnemy->getId() << std::endl;
    }

    timer = 0.0f; // Reset the timer after activation
}

void MOABEliminatorSkill::inActivateSkill() {
    // do nothin
}