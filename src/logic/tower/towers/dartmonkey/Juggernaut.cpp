#include "Juggernaut.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/JuggernautAttack.h"

#include "UltraJuggernaut.h"

Juggernaut::Juggernaut() 
    : Upgrade("Juggernaut", 1800, "Hurls a giant spiked ball that pops lead and excels at crushing Ceramic and Fortified Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<UltraJuggernaut>(); // Temporary lmao
    tag = "Juggernaut";
}

Juggernaut::Juggernaut(const Juggernaut& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Juggernaut::clone() const {
    return std::make_unique<Juggernaut>(*this);
}

void Juggernaut::loadTexture() {
    // Load the texture for Juggernaut upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/JuggernautUpgradeIcon.png");
}

void Juggernaut::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    for (auto& attack : attacks) {
        /**
         * * range = 128.0f
         * * cooldown = 1.0f
         * * damage = 2
         * * speed = 600
         * * pierce = 61
         * * lifeSpan = 1.0f
         * * properties = {true, false, true, true, true, true} // canHitLead, canHitWhite, canHitBlack, canHitFrozen, canHitCamo, canHitPurple.
         */
        
        if (attack->getTag() == "SpikeOPultAttack") {
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<JuggernautAttack>(128.0f, 1.0f, attacks.back()->getPosition(), attacks.back()->getTowerId(), 2, 600, 61, 1.0f, BulletProperties{true, true, true, true, false, true}, BloonDebuff().getIKnockBack(0.15f, 6.0f).getIBonusDamage(5, 2, 0, 0), BloonDebuff().getIKnockBack(0.15f, 2.0f).getIBonusDamage(0, 2, 0, 0)); 
            attack->setAttackPattern(std::move(attackPattern));
        }
    }
}

std::unique_ptr<Upgrade> Juggernaut::buy() {
    return nextUpgrade->clone();
}