#include "CrossbowMaster.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ArrowCritAttack.h"

CrossbowMaster::CrossbowMaster() 
    : Upgrade("Crossbow Master", 21500, "Crossbow Master shoots really fast and devastates most Bloon types with ease.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Crossbow Master";
}

CrossbowMaster::CrossbowMaster(const CrossbowMaster& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> CrossbowMaster::clone() const {
    return std::make_unique<CrossbowMaster>(*this);
}

void CrossbowMaster::loadTexture() {
    // Load the texture for Crossbow Master upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/CrossbowMasterUpgradeIcon.png");
}

void CrossbowMaster::update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for (auto& attack : attacks) {
        /**
         * * range = 320.0f
         * * cooldown = 0.2375f
         * * damage = 8
         * * speed = 900
         * * pierce = 8
         * * lifeSpan = 0.3f
         * * properties = {false, true, true, false, true, true} // canHitLead, canHitWhite, canHitBlack, canHitFrozen, canHitCamo, canHitPurple.
         */

        if (attack->getTag() == "ArrowCritAttack") {
            attacks.back() = std::make_unique<ArrowCritAttack>(320.0f, 0.2375f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 8, 900, 8, 0.3f, BulletProperties{false, true, true, false, true, true}, 5); 
        }
    }
}

std::unique_ptr<Upgrade> CrossbowMaster::buy() {
    return nextUpgrade->clone();
}