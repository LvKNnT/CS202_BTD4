#include "Distraction.h"
#include "../../../../core/Game.h"

#include "CounterEspionage.h"

Distraction::Distraction() 
    : Upgrade("Distraction", 250, "Some Bloons will become distracted and move backwards.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<CounterEspionage>(); // Temporary lmao
    tag = "Distraction";
}

Distraction::Distraction(const Distraction& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Distraction::clone() const {
    return std::make_unique<Distraction>(*this);
}

void Distraction::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/DistractionUpgradeIcon.png");
}

void Distraction::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto &attack:attacks) {
        if(attack->getTag() == "ShurikenAttack") {
            attack->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 15);
        } else if(attack->getTag() == "CaltropsAttack") {
            attack->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 10);
        } else if(attack->getTag() == "FlashBombAttack") {
            attack->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 30);
        } else if(attack->getTag() == "StickyBombAttack") {
            attack->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 15);
        }
    }
    // Distance Unit 120
}

std::unique_ptr<Upgrade> Distraction::buy() {
    return nextUpgrade->clone();
}