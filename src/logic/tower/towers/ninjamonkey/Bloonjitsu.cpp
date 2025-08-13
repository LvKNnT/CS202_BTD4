#include "Bloonjitsu.h"
#include "../../../../core/Game.h"

#include "../../../attack/patterns/QuintupleAttack.h"
#include "GrandmasterNinja.h"

Bloonjitsu::Bloonjitsu() 
    : Upgrade("Bloonjitsu", 2750, "Throws 5 shurikens at once!") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<GrandmasterNinja>(); // Temporary lmao
    tag = "Bloonjitsu";
}

Bloonjitsu::Bloonjitsu(const Bloonjitsu& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Bloonjitsu::clone() const {
    return std::make_unique<Bloonjitsu>(*this);
}

void Bloonjitsu::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/BloonjitsuUpgradeIcon.png");
}

void Bloonjitsu::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto& attack : attacks) {
        if(attack->getTag() == "ShurikenAttack") {
            attack->setAttackPattern(std::make_unique<QuintupleAttack>());
        }
    }
}

std::unique_ptr<Upgrade> Bloonjitsu::buy() {
    return nextUpgrade->clone();
}