#include "TripleShot.h"
#include "../../../../core/Game.h"

#include "../../../attack/patterns/TripleAttack.h"

#include "SuperMonkeyFanClubUpgrade.h"

TripleShot::TripleShot() 
    : Upgrade("Triple Shot", 450, "Throws 3 darts at a time instead of 1.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SuperMonkeyFanClubUpgrade>(); 
    tag = "Triple Shot";
}

TripleShot::TripleShot(const TripleShot& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> TripleShot::clone() const {
    return std::make_unique<TripleShot>(*this);
}

void TripleShot::loadTexture() {
    // Load the texture for Triple Shot upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/TripleShotUpgradeIcon.png");
}

void TripleShot::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    attackBuff.cooldownRatio *= 0.7f;

    for (auto& attack : attacks) {
        // Set the attack pattern to TripleAttack
        attackPattern = std::make_unique<TripleAttack>();
    }
}

std::unique_ptr<Upgrade> TripleShot::buy() {
    return nextUpgrade->clone();
}