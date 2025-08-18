#include "SnowstormSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

SnowstormSkill::SnowstormSkill()
    : Skill(30.0f, "Snowstorm Skill") {
    // Instant cooldown
    timer = cooldown - 10.0f;
}

std::unique_ptr<Skill> SnowstormSkill::clone() const {
    return std::make_unique<SnowstormSkill>(*this);
}

void SnowstormSkill::loadTexture() {
    // Load the texture for the Elite Sniper Passive skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Ice_Monkey/SnowstormUpgradeIcon.png");
}

void SnowstormSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool SnowstormSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float SnowstormSkill::getCooldown() const {
    return cooldown;
}

void SnowstormSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    for (auto& enemy : enemies) {
        if (enemy) {
            // Freeze
            if(SkillFriendAccess::getEnemyType(*enemy) == BloonType::Lead ||
               SkillFriendAccess::getEnemyType(*enemy) == BloonType::Ddt) {
                if(SkillFriendAccess::getAttackBuff(*tower).properties.canLead) {
                    enemy->setDebuff(BloonDebuff().getIFreeze(6.0f), BloonDebuff().getIFreeze(3.0f));
                }
            } else if(SkillFriendAccess::getEnemyType(*enemy) == BloonType::White ||
                      SkillFriendAccess::getEnemyType(*enemy) == BloonType::Zebra) {
                enemy->setDebuff(BloonDebuff().getIFreeze(3.0f), BloonDebuff().getIFreeze(3.0f));
            }
            else {
                enemy->setDebuff(BloonDebuff().getIFreeze(6.0f), BloonDebuff().getIFreeze(3.0f));
            }


        }
    }

    // Reset the timer after activation
    timer = 0.0f;
    MySound skillSound("ActivateSkill");
    skillSound.start();
}

void SnowstormSkill::inActivateSkill() {
    // do nothing
}

