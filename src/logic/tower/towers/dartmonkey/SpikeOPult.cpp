#include "SpikeOPult.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/SpikeOPultAttack.h"

#include "Juggernaut.h"

SpikeOPult::SpikeOPult() 
    : Upgrade("Spike-O-Pult", 320, "Converts the Dart Monkey into a slower attacking Spike-o-pult that hurls large spiked balls. Each ball can pop lots of Bloons and rebounds off obstacles.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Juggernaut>(); // Temporary lmao
    tag = "Spike-O-Pult";
}

SpikeOPult::SpikeOPult(const SpikeOPult& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SpikeOPult::clone() const {
    return std::make_unique<SpikeOPult>(*this);
}

void SpikeOPult::loadTexture() {
    // Load the texture for Spike-O-Pult upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/Spike-o-pultUpgradeIcon.png");
}

void SpikeOPult::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    bool isFound = false;

    for (auto& attack : attacks) {
        /**
         * * range = 128.0f
         * * cooldown = 1.15f
         * * * damage = 2
         * * * speed = 300
         * * * pierce = 19
         * * * lifeSpan = 1.0f
         * * * properties = {false, false, true, tru, true} // canHitLead, canHitWhite, canHitBlack, canHitFrozen, canHitCamo, canHitPurple.
         */

        if (attack->getTag() == "DartAttack") {
            attack = std::make_unique<SpikeOPultAttack>(128.0f, 1.15f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 1, 300, 19, 10.0f, BulletProperties{false, true, true, true, false, true}); 
            isFound = true;
        }
    }
    
    attackBuff.rangeRatio *= 1.15f;
    
    if (!isFound) {
        attacks.push_back(std::make_unique<SpikeOPultAttack>(128.0f, 1.15f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 1, 300, 19, 10.0f, BulletProperties{false, true, true, true, false, true})); 
    }
}

std::unique_ptr<Upgrade> SpikeOPult::buy() {
    return nextUpgrade->clone();
}