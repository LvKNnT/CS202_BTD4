#include "SharpShooter.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ArrowCritAttack.h"

#include "CrossbowMaster.h"

SharpShooter::SharpShooter() 
    : Upgrade("Sharp Shooter", 2050, "Sharp Shooter attacks faster and does powerful Crit shots every few shots that do a lot more damage.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<CrossbowMaster>(); // Temporary lmao
    tag = "Sharp Shooter";
}

SharpShooter::SharpShooter(const SharpShooter& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SharpShooter::clone() const {
    return std::make_unique<SharpShooter>(*this);
}

void SharpShooter::loadTexture() {
    // Load the texture for Sharp Shooter upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/SharpShooterUpgradeIcon.png");
}

void SharpShooter::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) {
    for (auto& attack : attacks) {
        /**
         * * range = 240.0f
         * * cooldown = 0.475f
         * * damage = 6
         * * speed = 1200
         * * pierce = 3
         * * lifeSpan = 0.3f
         * * properties = {false, true, true, false, false, true} // canHitLead, canHitWhite, canHitBlack, canHitFrozen, canHitCamo, canHitPurple.
         * * maxCounter = 10
         */

        if (attack->getTag() == "ArrowAttack") {
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attacks.back() = std::make_unique<ArrowCritAttack>(240.0f, 0.475f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 6, 1200, 3, 0.3f, BulletProperties{false, true, true, false, false, true}, BloonDebuff(), BloonDebuff(), 10); 
            attacks.back()->setAttackPattern(std::move(attackPattern));
        }
    }
}

std::unique_ptr<Upgrade> SharpShooter::buy() {
    return nextUpgrade->clone();
}