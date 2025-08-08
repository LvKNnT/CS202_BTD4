#include "DoubleShot.h"
#include "../../../../core/Game.h"

#include "../../../attack/patterns/DoubleAttack.h"
#include "Bloonjitsu.h"

DoubleShot::DoubleShot() 
    : Upgrade("Double Shot", 900, "Throws 2 shurikens at once.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Bloonjitsu>(); // Temporary lmao
    tag = "Double Shot";
}

DoubleShot::DoubleShot(const DoubleShot& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> DoubleShot::clone() const {
    return std::make_unique<DoubleShot>(*this);
}

void DoubleShot::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/DoubleShotUpgradeIcon.png");
}

void DoubleShot::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto& attack : attacks) {
        if(attack->getTag() == "ShurikenAttack") {
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack->setAttackPattern(std::make_unique<DoubleAttack>());
            attack->setAttackPattern(std::move(attackPattern));
        }
    }
}

std::unique_ptr<Upgrade> DoubleShot::buy() {
    return nextUpgrade->clone();
}