#include "FragBombs.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/FragBombsAttack.h"

#include "ClusterBombs.h"

FragBombs::FragBombs() 
    : Upgrade("Frag Bombs", 300, "Explosions throw sharp fragments that can pop more Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ClusterBombs>(); // Temporary lmao
    tag = "Frag Bombs";
}

FragBombs::FragBombs(const FragBombs& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FragBombs::clone() const {
    return std::make_unique<FragBombs>(*this);
}

void FragBombs::loadTexture() {
    // Load the texture for Frag Bombs upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/FragBombsUpgradeIcon.png");
}

void FragBombs::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    attackBuff.range += 8.0f;
    attackBuff.lifeSpanRatio *= 1.05f;
    
    bool hasBombAttack = false;
    for (auto& attack : attacks) {
        if (attack->getTag() == "BombAttack") {
            /**
             * * range = 160.0f
             * * cooldown = 1.5f
             * * damage = 1
             * * speed = 360
             * * pierce = 22
             * * lifeSpan = 2.0f
             * * properties = {true, false, true, true, false, true} // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
             */
            attack = std::make_unique<FragBombsAttack>(160.0f, 1.5f, attack->getPosition(), attack->getTowerId(), 1, 360, 22, 2.0f,
                BulletProperties{true, false, true, true, false, true}, 
                BloonDebuff(), 
                BloonDebuff());

            hasBombAttack = true;
        }
    }

    if (!hasBombAttack) {
        attacks.push_back(std::make_unique<FragBombsAttack>(160.0f, 1.5f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 1, 360, 22, 2.0f,
            BulletProperties{true, false, true, true, false, true}, 
            BloonDebuff(), 
            BloonDebuff()));
    }
}

std::unique_ptr<Upgrade> FragBombs::buy() {
    return nextUpgrade->clone();
}
