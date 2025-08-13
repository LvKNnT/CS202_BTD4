#include "BloonSabotageSkill.h"
#include <iostream>
#include "raymath.h"
#include <algorithm>

#include "../../../core/Game.h"

BloonSabotageSkill::BloonSabotageSkill()
    : Skill(60.0f, "Bloon Sabotage") {
    // Instant cooldown
    duration = 15.0f;
    timer = 0;
    isSkillActivating = true;
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

bool BloonSabotageSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    if(isSkillActivating && timer < duration) return true;
    if(!isSkillActivating && timer >= cooldown) return true;
    return false;
}

float BloonSabotageSkill::getCooldown() const {
    return cooldown;
}

void BloonSabotageSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    for(auto &enemy:enemies) {
        if(SkillFriendAccess::getEnemyType(*enemy) == BloonType::Bad) continue;
        enemy->setDebuff(BloonDebuff().getISlow(0.5f, duration - timer), BloonDebuff().getISlow(0.5f, duration - timer));
    }

    closestTower = tower;
    // Buff the closest towers
    SkillFriendAccess::getTag(*tower) = "Bloon Sabotage Ninja"; // Change the tag to Bloon Sabotage Ninja

    // Vector2 position = SkillFriendAccess::getTowerPosition(*tower);
    // Animation skillSprite("sharingan", (Vector2) {position.x - 30, position.y - 30}, 60, 60, 4, 0.125f);
    // skillSprite.start();
    // Game::Instance().getAnimationManager().addAnimation(skillSprite);

    if(timer == 0.0f) std::cerr << "Activated Bloon Sabotage skill for 1 towers." << std::endl;
}

void BloonSabotageSkill::inActivateSkill() {
    if(timer < duration) return; // Only deactivate if the skill is still active
    // Reset the attack buffs of the closest towers
    SkillFriendAccess::getTag(*closestTower) = "NinjaMonkey"; // Reset the tag to Ninja Monkey
    std::cerr << "Deactivated Bloon Sabotage skill." << std::endl;
}