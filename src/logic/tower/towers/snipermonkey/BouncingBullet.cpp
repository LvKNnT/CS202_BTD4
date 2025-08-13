#include "BouncingBullet.h"
#include "../../../../core/Game.h"

#include "SupplyDrop.h"

BouncingBullet::BouncingBullet() 
    : Upgrade("Bouncing Bullet", 2100, "Shots bounce to new targets up to 2 times.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SupplyDrop>(); // No further upgrade available
    tag = "Bouncing Bullet";
}

BouncingBullet::BouncingBullet(const BouncingBullet& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BouncingBullet::clone() const {
    return std::make_unique<BouncingBullet>(*this);
}

void BouncingBullet::loadTexture() {
    // Load the texture for Bouncing Bullet upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/BouncingBulletUpgradeIcon.png");
}

void BouncingBullet::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.pierce += 2; // Increase pierce by 2 for bouncing bullets
    
    for(auto& attack : attacks) {
        if (attack->getTag() == "ShrapnelShotAttack") {
            attack->getProperties() += BulletProperties::normal().getITracing(200.0f, TargetPriority::First, true);
        }
    }
}

std::unique_ptr<Upgrade> BouncingBullet::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}