#include "SharpShurikens.h"
#include "../../../../core/Game.h"

#include "DoubleShot.h"

SharpShurikens::SharpShurikens() 
    : Upgrade("Sharp Shurikens", 350, "Shurikens can pop 4 Bloons each.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<DoubleShot>(); // Temporary lmao
    tag = "Sharp Shurikens";
}

SharpShurikens::SharpShurikens(const SharpShurikens& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SharpShurikens::clone() const {
    return std::make_unique<SharpShurikens>(*this);
}

void SharpShurikens::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/SharpShurikensUpgradeIcon.png");
}

void SharpShurikens::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for(auto& attack : attacks) {
        attackBuff.pierce += 2;
    }
}

std::unique_ptr<Upgrade> SharpShurikens::buy() {
    return nextUpgrade->clone();
}