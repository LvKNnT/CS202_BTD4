#include "Crossbow.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ArrowAttack.h"

#include "SharpShooter.h"

CrossBow::CrossBow() 
    : Upgrade("Crossbow", 575 , "Uses a long range Crossbow that can pop 3 layers of Bloon for every hit.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SharpShooter>(); // Temporary lmao
    tag = "Crossbow";
}

CrossBow::CrossBow(const CrossBow& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> CrossBow::clone() const {
    return std::make_unique<CrossBow>(*this);
}

void CrossBow::loadTexture() {
    // Load the texture for Crossbow upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/CrossbowUpgradeIcon.png");
}

void CrossBow::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) {
    bool isFound = false;

    for (auto& attack : attacks) {
        /**
         * * range = 240.0f
         * * cooldown = 0.95f
         * * damage = 3
         * * speed = 800
         * * pierce = 3
         * * lifeSpan = 0.31640625f
         * * properties = {false, true, true, false, true, true} // canHitLead, canHitWhite, canHitBlack, canHitFrozen, canHitCamo, canHitPurple.
         */

        if(attack->getTag() == "DartAttack") {
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<ArrowAttack>(240.0f, 0.95f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 3, 800, 3, 0.31640625f, BulletProperties{false, true, true, false, true, true}, BloonDebuff(), BloonDebuff()); 
            attack->setAttackPattern(std::move(attackPattern));
            isFound = true;    
        }
    }

    if(!isFound) {
        std::unique_ptr<AttackPattern> attackPattern = attacks.back()->getAttackPattern()->clone();
        attacks.push_back(std::make_unique<ArrowAttack>(240.0f, 0.95f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 3, 800, 3, 0.31640625f, BulletProperties{false, true, true, false, true, true}, BloonDebuff(), BloonDebuff())); 
        attacks.back()->setAttackPattern(std::move(attackPattern));
    }
}

std::unique_ptr<Upgrade> CrossBow::buy() {
    return nextUpgrade->clone();
}