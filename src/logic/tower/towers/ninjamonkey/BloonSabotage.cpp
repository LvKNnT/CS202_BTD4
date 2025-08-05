#include "BloonSabotage.h"
#include "../../../../core/Game.h"

#include "GrandSaboteur.h"

BloonSabotage::BloonSabotage() 
    : Upgrade("Bloon Sabotage", 5200, "Sabotage ability: Lasts 15 seconds. During the sabotage, all Bloons move at half speed.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<GrandSaboteur>(); // Temporary lmao
    tag = "Bloon Sabotage";
}

BloonSabotage::BloonSabotage(const BloonSabotage& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BloonSabotage::clone() const {
    return std::make_unique<BloonSabotage>(*this);
}

void BloonSabotage::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/BloonSabotageUpgradeIcon.png");
}

void BloonSabotage::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for(auto& attack : attacks) {
        // Ability slows down all bloons on screen and any incoming bloons by 50% for 15 seconds. Cannot soak through MOAB-class layers nor affect BADs and Bosses.   
    }
}

std::unique_ptr<Upgrade> BloonSabotage::buy() {
    return nextUpgrade->clone();
}