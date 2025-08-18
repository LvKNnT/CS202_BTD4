#include "EliteDefenderPassiveSkill.h"
#include "../../../core/Game.h"

EliteDefenderPassiveSkill::EliteDefenderPassiveSkill()
    : Skill(0.0f, "Elite Defender Passive") {
    // Instant cooldown
    timer = 0.0f; // Initialize timer to 0
    lastCooldownBuff = 1.0f; // Initialize the last cooldown buff
}

std::unique_ptr<Skill> EliteDefenderPassiveSkill::clone() const {
    return std::make_unique<EliteDefenderPassiveSkill>(*this);
}

void EliteDefenderPassiveSkill::loadTexture() {
    // Load the texture for the Elite Defender Passive skill
    // Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Sniper_Monkey/EliteDefenderPassiveUpgradeIcon.png");
}

void EliteDefenderPassiveSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool EliteDefenderPassiveSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float EliteDefenderPassiveSkill::getCooldown() const {
    return cooldown;
}

void EliteDefenderPassiveSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    // Apply the cooldown buff to the tower
    SkillFriendAccess::getAttackBuff(*tower).cooldownRatio /= lastCooldownBuff;

    auto enemy = enemies.begin();
    float distanceToTrackEnd = mapManager.getCurrentMap().
        distanceToEndPoint(SkillFriendAccess::getEnemyPosition(*(*enemy)), 
                           SkillFriendAccess::getTrackIndex(*(*enemy)), 
                        SkillFriendAccess::getPathIndex(*(*enemy)));
    float totalDistance = mapManager.getCurrentMap().getTotalDistance();

    // Reduce cooldown up to 0.5f based on the distance left
    float reduction = 1.0f - (distanceToTrackEnd / totalDistance);
    lastCooldownBuff = 1.0f - reduction * 0.5f; // cooldownRatio will be between 1.0f and 0.5f

    SkillFriendAccess::getAttackBuff(*tower).cooldownRatio *= lastCooldownBuff;

    // std::cerr << "Elite Defender Passive Skill activated! Cooldown reduced by: " 
    //           << (1.0f - SkillFriendAccess::getAttackBuff(*tower).cooldownRatio) * 100.0f 
    //           << "%, new cooldown ratio: " 
    //           << SkillFriendAccess::getAttackBuff(*tower).cooldownRatio << std::endl;

    // Reset the timer after activation
    timer = 0.0f;
    MySound skillSound("ActivateSkill");
    skillSound.start();
}

void EliteDefenderPassiveSkill::inActivateSkill() {
}