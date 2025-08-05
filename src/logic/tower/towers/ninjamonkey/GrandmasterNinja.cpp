#include "GrandmasterNinja.h"
#include "../../../../core/Game.h"

#include "../../../attack/patterns/OctupleAttack.h"

GrandmasterNinja::GrandmasterNinja() 
    : Upgrade("Grandmaster Ninja", 35000, "Throws incredibly fast, 8 shurikens per shot!") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Grandmaster Ninja";
}

GrandmasterNinja::GrandmasterNinja(const GrandmasterNinja& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> GrandmasterNinja::clone() const {
    return std::make_unique<GrandmasterNinja>(*this);
}

void GrandmasterNinja::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/GrandmasterNinjaUpgradeIcon.png");
}

void GrandmasterNinja::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for(auto& attack : attacks) {
        attackPattern = std::make_unique<OctupleAttack>();
        attackBuff.damage += 1;
        attackBuff.cooldownRatio *= 0.31f;
        attackBuff.range += 10;
    }
}

std::unique_ptr<Upgrade> GrandmasterNinja::buy() {
    return nextUpgrade->clone();
}