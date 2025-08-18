#include "BloontoniumReactor.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/SubmergeAttack.h"

#include "Energizer.h"

BloontoniumReactor::BloontoniumReactor() 
    : Upgrade("Bloontonium Reactor", 2300, "Submerge can pop Bloons") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Energizer>(); // Temporary lmao
    tag = "Bloontonium Reactor";
}

BloontoniumReactor::BloontoniumReactor(const BloontoniumReactor& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BloontoniumReactor::clone() const {
    return std::make_unique<BloontoniumReactor>(*this);
}

void BloontoniumReactor::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/BloontoniumReactorUpgradeIcon.png");
}

void BloontoniumReactor::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 1;
    
    for(auto& attack : attacks) {
        if (attack->getTag() == "SubmergeAttack") {
            attack->setPierce(attack->getPierce() * 0.5f); // Increase pierce of SubmergeAttack
            attack->setCooldown(0.28f); // Decrease cooldown of SubmergeAttack
        }
    }
}

std::unique_ptr<Upgrade> BloontoniumReactor::buy() {
    return nextUpgrade->clone();
}