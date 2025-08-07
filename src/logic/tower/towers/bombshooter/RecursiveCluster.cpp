#include "RecursiveCluster.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/RecursiveClusterAttack.h"

#include "BombBlizt.h"

RecursiveCluster::RecursiveCluster() 
    : Upgrade("Recursive Cluster", 2500, "Every second shot the cluster bombs send out more cluster bombs for even more destruction.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<BombBlizt>(); // Temporary lmao
    tag = "Recursive Cluster";
}

RecursiveCluster::RecursiveCluster(const RecursiveCluster& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> RecursiveCluster::clone() const {
    return std::make_unique<RecursiveCluster>(*this);
}

void RecursiveCluster::loadTexture() {
    // Load the texture for Cluster Bombs upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/RecursiveClusterUpgradeIcon.png");
}

void RecursiveCluster::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {    
    bool hasBombAttack = false;
    for (auto& attack : attacks) {
        if (attack->getTag() == "ClusterBombsAttack") {
            /**
             * * range = 160.0f
             * * cooldown = 1.5f
             * * damage = 2
             * * speed = 360
             * * pierce = 22
             * * lifeSpan = 2.0f 
             * * properties = {true, false, true, true, false, true} // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
             */
            attack = std::make_unique<RecursiveClusterAttack>(160.0f, 1.5f, attack->getPosition(), attack->getTowerId(), 2, 360, 22, 2.0f,
                BulletProperties{true, false, true, true, false, true}, 
                BloonDebuff(), 
                BloonDebuff());

            hasBombAttack = true;
        }
    }

    if (!hasBombAttack) {
        attacks.push_back(std::make_unique<RecursiveClusterAttack>(160.0f, 1.5f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 1, 360, 22, 2.0f,
            BulletProperties{true, false, true, true, false, true}, 
            BloonDebuff(), 
            BloonDebuff()));
    }
}

std::unique_ptr<Upgrade> RecursiveCluster::buy() {
    return nextUpgrade->clone();
}