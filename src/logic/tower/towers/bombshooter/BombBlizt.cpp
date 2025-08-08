#include "BombBlizt.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/BombBliztAttack.h"

BombBlizt::BombBlizt() 
    : Upgrade("Recursive Cluster", 23000, "Deals much more damage and gains the passive Bomb Storm Ability - when lives are lost, the Bomb Storm automatically triggers, which destroys all but the biggest of Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Recursive Cluster";
}

BombBlizt::BombBlizt(const BombBlizt& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BombBlizt::clone() const {
    return std::make_unique<BombBlizt>(*this);
}

void BombBlizt::loadTexture() {
    // Load the texture for Cluster Bombs upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/BombBliztUpgradeIcon.png");
}

void BombBlizt::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {    
    bool hasBombAttack = false;
    for (auto& attack : attacks) {
        if (attack->getTag() == "RecursiveClusterAttack") {
            /**
             * * range = 160.0f
             * * cooldown = 1.5f
             * * damage = 2
             * * speed = 360
             * * pierce = 22
             * * lifeSpan = 2.0f 
             * * properties = {true, false, true, true, false, true} // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
             */
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<BombBliztAttack>(160.0f, 1.5f, attack->getPosition(), attack->getTowerId(), 2, 360, 22, 2.0f,
                BulletProperties{true, false, true, true, false, true}, 
                BloonDebuff(), 
                BloonDebuff());
            attack->setAttackPattern(std::move(attackPattern));
            
            hasBombAttack = true;
        }
    }
}

std::unique_ptr<Upgrade> BombBlizt::buy() {
    return nextUpgrade->clone();
}