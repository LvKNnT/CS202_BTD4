#include "UltraJuggernaut.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/UltraJuggernautAttack.h"

UltraJuggernaut::UltraJuggernaut() 
    : Upgrade("Ultra-Juggernaut", 15000, "Gigantic spiked ball splits twice into 6 Juggernaut balls for even more destructive power against Ceramic, Fortified and Lead Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Ultra-Juggernaut";
}

UltraJuggernaut::UltraJuggernaut(const UltraJuggernaut& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> UltraJuggernaut::clone() const {
    return std::make_unique<UltraJuggernaut>(*this);
}

void UltraJuggernaut::loadTexture() {
    // Load the texture for Ultra Juggernaut upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/UltraJuggernautUpgradeIcon.png");
}

void UltraJuggernaut::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    for (auto& attack : attacks) {
        /**
         * * range = 128.0f
         * * cooldown = 1.0f
         * * damage = 5
         * * speed = 600
         * * pierce = 210
         * * lifeSpan = 1.0f
         * * properties = {true, true, true, true, false, true} // canHitLead, canHitWhite, canHitBlack, canHitFrozen, canHitCamo, canHitPurple.
         */

        if (attack->getTag() == "JuggernautAttack") {
            attack = std::make_unique<UltraJuggernautAttack>(128.0f, 1.0f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 5, 600, 210, 10.0f, BulletProperties{true, true, true, true, false, true}, BloonDebuff().getIKnockBack(0.15f, 6.0f), BloonDebuff().getIKnockBack(0.15f, 2.0f)); 
        }
    }
}

std::unique_ptr<Upgrade> UltraJuggernaut::buy() {
    return nextUpgrade->clone();
}

