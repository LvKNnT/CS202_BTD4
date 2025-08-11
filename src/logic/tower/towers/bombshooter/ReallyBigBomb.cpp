#include "ReallyBigBombs.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ReallyBigBombsAttack.h"

#include "BloonImpact.h"

ReallyBigBombs::ReallyBigBombs() 
    : Upgrade("Really Big Bombs", 1100, "Huge bombs deal greater damage in a large area and knock Bloons back along the path.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<BloonImpact>(); // Temporary lmao
    tag = "Really Big Bombs";
}

ReallyBigBombs::ReallyBigBombs(const ReallyBigBombs& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ReallyBigBombs::clone() const {
    return std::make_unique<ReallyBigBombs>(*this);
}

void ReallyBigBombs::loadTexture() {
    // Load the texture for Really Big Bombs upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/ReallyBigBombsUpgradeIcon.png");
}

void ReallyBigBombs::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    
    bool hasBombAttack = false;
    for(auto& attack : attacks) {
        if (attack->getTag() == "BombAttack") {
            /**
             * * range = 160.0f
             * * cooldown = 1.5f
             * * damage = 4
             * * speed = 360
             * * pierce = 80
             * * lifeSpan = 2.0f
             * * properties = {true, false, true, true, false, true} // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
             */
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<ReallyBigBombsAttack>(160.0f, 1.5f, attack->getPosition(), attack->getTowerId(), 4, 360, 80, 2.0f, 
                BulletProperties{true, false, true, true, false, true}, 
                BloonDebuff().getIKnockBack(0.1f, 6.0f), 
                BloonDebuff());
            attack->setAttackPattern(std::move(attackPattern));

            hasBombAttack = true;
        }
    }

    if(!hasBombAttack) {
        std::unique_ptr<AttackPattern> attackPattern = attacks.back()->getAttackPattern()->clone();
        attacks.push_back(std::make_unique<ReallyBigBombsAttack>(160.0f, 1.5f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 4, 360, 80, 2.0f, 
            BulletProperties{true, false, true, true, false, true}, 
            BloonDebuff().getIKnockBack(0.1f, 6.0f), 
            BloonDebuff()));
        attacks.back()->setAttackPattern(std::move(attackPattern));
    }
}

std::unique_ptr<Upgrade> ReallyBigBombs::buy() {
    return nextUpgrade->clone();
}
