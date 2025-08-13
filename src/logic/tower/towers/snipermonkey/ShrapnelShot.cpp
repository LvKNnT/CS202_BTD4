#include "ShrapnelShot.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ShrapnelShotAttack.h"
#include "../../../attack/patterns/NormalAttack.h"

#include "BouncingBullet.h"

ShrapnelShot::ShrapnelShot() 
    : Upgrade("Shrapnel Shot", 450, "Damaged bloons spray out a cone of sharp shrapnel.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<BouncingBullet>(); // No further upgrade available
    tag = "Shrapnel Shot";
}

ShrapnelShot::ShrapnelShot(const ShrapnelShot& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ShrapnelShot::clone() const {
    return std::make_unique<ShrapnelShot>(*this);
}

void ShrapnelShot::loadTexture() {
    // Load the texture for Shrapnel Shot upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/ShrapnelShotUpgradeIcon.png");
}

void ShrapnelShot::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    // Update the attack pattern to use ShrapnelShotAttack
    for (auto& attack : attacks) {
        /**
         * * range = full map
         * * cooldown = 1.59f
         * * * damage = 2
         * * * speed = 32000
         * * * pierce = 1
         * * * lifeSpan = 2000.0f
         * * * properties = BulletProperties::normal()
         */

        if (attack->getTag() == "DartAttack") {
            std::unique_ptr<AttackPattern> newPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<ShrapnelShotAttack>(
                attack->getRange(),
                attack->getCooldown(),
                attack->getPosition(),
                attack->getTowerId(),
                attack->getDamage(),
                attack->getSpeed(),
                attack->getPierce(),
                attack->getLifeSpan(),
                attack->getProperties(),
                attack->getNormalDebuff(),
                attack->getMoabDebuff()
            );
            attack->setAttackPattern(std::move(newPattern));
            break; // Assuming only one DartAttack exists
        }
    }
}

std::unique_ptr<Upgrade> ShrapnelShot::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}