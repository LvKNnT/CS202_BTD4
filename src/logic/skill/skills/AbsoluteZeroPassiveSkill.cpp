#include "AbsoluteZeroPassiveSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

AbsoluteZeroPassiveSkill::AbsoluteZeroPassiveSkill()
    : Skill(0.0f, "Absolute Zero Passive Skill") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> AbsoluteZeroPassiveSkill::clone() const {
    return std::make_unique<AbsoluteZeroPassiveSkill>(*this);
}

void AbsoluteZeroPassiveSkill::loadTexture() {
    // Load the texture for the Elite Sniper Passive skill
    // Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Sniper_Monkey/EliteSniperPassiveUpgradeIcon.png");
}

void AbsoluteZeroPassiveSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool AbsoluteZeroPassiveSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float AbsoluteZeroPassiveSkill::getCooldown() const {
    return cooldown;
}

void AbsoluteZeroPassiveSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
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
            enemy->setDebuff(BloonDebuff().getISlow(0.6f, GetFrameTime()), BloonDebuff().getISlow(0.3f, GetFrameTime())); 
        }
    }

    // Reset the timer after activation
    timer = 0.0f;
}

void AbsoluteZeroPassiveSkill::inActivateSkill() {
    // do nothin
}

