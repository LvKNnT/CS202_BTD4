#include "SubCommanderSkill.h"
#include <iostream>
#include "raymath.h"

#include "../../../core/Game.h"

SubCommanderSkill::SubCommanderSkill()
    : Skill(0.0f, "Absolute Zero Skill") {
    // Instant cooldown
    timer = cooldown;
}

std::unique_ptr<Skill> SubCommanderSkill::clone() const {
    return std::make_unique<SubCommanderSkill>(*this);
}

void SubCommanderSkill::loadTexture() {
    // Load the texture for the Elite Sniper Passive skill
    Game::Instance().getTextureManager().loadTexture(name, "../assets/tower/Monkey_Sub/SubCommanderUpgradeIcon.png");
}

void SubCommanderSkill::update() {
    // Update the skill timer
    if (timer < cooldown) {
        timer += GetFrameTime();
    }

}

bool SubCommanderSkill::canActivateSkill() const {
    // Check if the skill is ready to be activated
    return timer >= cooldown;
}

float SubCommanderSkill::getCooldown() const {
    return cooldown;
}

void SubCommanderSkill::activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) {
    if (!tower) return;
    if (!canActivateSkill()) return;

    // Buff all Monkey Subs within the skill tower's range
    float skillRange = 0.0f;
    for(auto& attack : SkillFriendAccess::getAttacks(*tower)) {
        skillRange = std::max(skillRange, attack->getRange());
    }
    Vector2 skillPos = SkillFriendAccess::getTowerPosition(*tower);

    for (auto& otherTower : towers) {
        if (!otherTower) continue;

        if (SkillFriendAccess::getTowerType(*otherTower) == TowerType::MonkeySub) {
            if(affectedTowers.find(SkillFriendAccess::getTowerId(*otherTower)) != affectedTowers.end()) {
                continue; // Skip if this tower has already been buffed
            }

            Vector2 otherPos = SkillFriendAccess::getTowerPosition(*otherTower);
            float distance = Vector2Distance(skillPos, otherPos);

            if (distance <= skillRange) {
                SkillFriendAccess::getAttackBuff(*otherTower).cooldownRatio *= 0.5f; // Halve the attack cooldown
                SkillFriendAccess::getAttackBuff(*otherTower).pierce += 4;
                affectedTowers.insert(SkillFriendAccess::getTowerId(*otherTower)); // Store the affected tower
            }
        }
    }

    // Reset the timer after activation
    timer = 0.0f;
    //MySound skillSound("ActivateSkill");
    //skillSound.start();
}

void SubCommanderSkill::inActivateSkill() {
    // do nothing
}

