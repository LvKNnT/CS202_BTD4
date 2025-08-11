#include "ClusterBombs.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ClusterBombsAttack.h"

#include "RecursiveCluster.h"

ClusterBombs::ClusterBombs() 
    : Upgrade("Cluster Bombs", 700, "Throws out secondary bombs instead of sharp fragments every shot.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<RecursiveCluster>(); // Temporary lmao
    tag = "Cluster Bombs";
}

ClusterBombs::ClusterBombs(const ClusterBombs& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ClusterBombs::clone() const {
    return std::make_unique<ClusterBombs>(*this);
}

void ClusterBombs::loadTexture() {
    // Load the texture for Cluster Bombs upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/ClusterBombsUpgradeIcon.png");
}

void ClusterBombs::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) {    
    for (auto& attack : attacks) {
        if (attack->getTag() == "FragBombsAttack") {
            /**
             * * range = 160.0f
             * * cooldown = 1.5f
             * * damage = 1
             * * speed = 360
             * * pierce = 22
             * * lifeSpan = 2.0f
             * * properties = {true, false, true, true, false, true} // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
             */
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<ClusterBombsAttack>(160.0f, 1.5f, attack->getPosition(), attack->getTowerId(), 1, 360, 22, 2.0f,
                BulletProperties{true, false, true, true, false, true}, 
                BloonDebuff(), 
                BloonDebuff());
            attack->setAttackPattern(std::move(attackPattern));
        }
    }
}

std::unique_ptr<Upgrade> ClusterBombs::buy() {
    return nextUpgrade->clone();
}