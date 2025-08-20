#include "EliteSniperPassiveSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

EliteSniperPassiveSkill::EliteSniperPassiveSkill()
    : Skill(0.0f, "Elite Sniper Passive") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> EliteSniperPassiveSkill::clone() const {
    return std::make_unique<EliteSniperPassiveSkill>(*this);
}

void EliteSniperPassiveSkill::loadTexture() {
    // Load the texture for the Elite Sniper Passive skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Sniper_Monkey/EliteSniperPassiveUpgradeIcon.png");
}

void EliteSniperPassiveSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }
}

bool EliteSniperPassiveSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float EliteSniperPassiveSkill::getCooldown() const {
    return cooldown;
}

void EliteSniperPassiveSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    // Buff other Sniper Monkey towers
    for (const auto& t : towers) {
        if(t && SkillFriendAccess::getTowerType(*t) == TowerType::SniperMonkey
        && buffedTowerIds.find(SkillFriendAccess::getTowerId(*t)) == buffedTowerIds.end()) {
            SkillFriendAccess::getAttackBuff(*t).cooldownRatio *= 0.75;

            buffedTowerIds.insert(SkillFriendAccess::getTowerId(*t)); // Mark this tower as buffed
        }
    }

    // Reset the timer after activation
    timer = 0.0f;
    // MySound skillSound("ActivateSkill");
    // skillSound.start();
}

void EliteSniperPassiveSkill::inActivateSkill() {
    // Reset the skill state if needed
    timer = cooldown; // Reset the timer to cooldown
    std::cout << "Elite Sniper Passive skill deactivated." << std::endl;

}

