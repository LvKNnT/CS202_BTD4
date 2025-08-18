#include "ArcticWindSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

ArcticWindSkill::ArcticWindSkill()
    : Skill(0.0f, "Arctic Wind Skill") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> ArcticWindSkill::clone() const {
    return std::make_unique<ArcticWindSkill>(*this);
}

void ArcticWindSkill::loadTexture() {
    // Load the texture for the Elite Sniper Passive skill
    // Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Sniper_Monkey/EliteSniperPassiveUpgradeIcon.png");
}

void ArcticWindSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool ArcticWindSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float ArcticWindSkill::getCooldown() const {
    return cooldown;
}

void ArcticWindSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    float range = 0.0f;
    for(const auto& attack : SkillFriendAccess::getAttacks(*tower)) {
        range = std::max(range, attack->getRange() * SkillFriendAccess::getAttackBuff(*tower).rangeRatio + SkillFriendAccess::getAttackBuff(*tower).range);
    }
    range += 10.0f;
    Vector2 towerPos = SkillFriendAccess::getTowerPosition(*tower);

    for (auto& enemy : enemies) {
        if (!enemy) continue;
        Vector2 enemyPos = enemy->getPosition();
        float distance = Vector2Distance(towerPos, enemyPos);
        if (distance <= range) {
            // Apply the slow effect to the enemy
            enemy->setDebuff(BloonDebuff().getISlow(0.4f, GetFrameTime()), BloonDebuff()); 
        }
    }

    // Reset the timer after activation
    timer = 0.0f;
}

void ArcticWindSkill::inActivateSkill() {
}

