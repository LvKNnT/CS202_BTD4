#include "NinjaDiscipline.h"
#include "../../../../core/Game.h"

#include "SharpShurikens.h"

NinjaDiscipline::NinjaDiscipline() 
    : Upgrade("Ninja Discipline", 350, "Increases attack speed.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SharpShurikens>(); // Temporary lmao
    tag = "Ninja Discipline";
}

NinjaDiscipline::NinjaDiscipline(const NinjaDiscipline& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> NinjaDiscipline::clone() const {
    return std::make_unique<NinjaDiscipline>(*this);
}

void NinjaDiscipline::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/NinjaDisciplineUpgradeIcon.png");
}

void NinjaDiscipline::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    for(auto& attack : attacks) {
        attackBuff.cooldownRatio *= 0.7;
    }
}

std::unique_ptr<Upgrade> NinjaDiscipline::buy() {
    return nextUpgrade->clone();
}