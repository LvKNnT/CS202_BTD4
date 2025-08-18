#include "Energizer.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/SubmergeAttack.h"

Energizer::Energizer() 
    : Upgrade("Energizer", 31000, "Greatly increases the power of Submerge and Support") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Energizer";
}

Energizer::Energizer(const Energizer& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Energizer::clone() const {
    return std::make_unique<Energizer>(*this);
}

void Energizer::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/EnergizerUpgradeIcon.png");
}

void Energizer::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 4;
    attackBuff.extraNormalDebuff.bonusDamage += 10;
    
    for(auto& attack : attacks) {
        if (attack->getTag() == "SubmergeAttack") {
            attack->setPierce(1000); // Increase pierce of SubmergeAttack
        }
    }
}

std::unique_ptr<Upgrade> Energizer::buy() {
    return nextUpgrade->clone();
}