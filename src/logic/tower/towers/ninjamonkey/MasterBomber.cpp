#include "MasterBomber.h"
#include "../../../../core/Game.h"

MasterBomber::MasterBomber() 
    : Upgrade("Master Bomber", 40000, "One Monkey MOAB demolition machine.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Master Bomber";
}

MasterBomber::MasterBomber(const MasterBomber& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MasterBomber::clone() const {
    return std::make_unique<MasterBomber>(*this);
}

void MasterBomber::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/MasterBomberUpgradeIcon.png");
}

void MasterBomber::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    for(auto& attack : attacks) {
    }
}

std::unique_ptr<Upgrade> MasterBomber::buy() {
    return nextUpgrade->clone();
}