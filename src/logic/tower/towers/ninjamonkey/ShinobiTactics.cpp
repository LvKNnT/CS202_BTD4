#include "ShinobiTactics.h"
#include "../../../../core/Game.h"

#include "GrandSaboteur.h"

ShinobiTactics::ShinobiTactics() 
    : Upgrade("Shinobi Tactics", 1200, "Increases attack speed and pierce of nearby Ninjas. Stacks 20 times.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<GrandSaboteur>(); // Temporary lmao
    tag = "Shinobi Tactics";
}

ShinobiTactics::ShinobiTactics(const ShinobiTactics& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ShinobiTactics::clone() const {
    return std::make_unique<ShinobiTactics>(*this);
}

void ShinobiTactics::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/ShinobiTacticsUpgradeIcon.png");
}

void ShinobiTactics::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) {
    for(auto& attack : attacks) {
        // Increases attack speed of itself and other Ninjas in range by +8% multiplicatively and pierce by +8% additively. Stacks up to 20 times.
    }
}

std::unique_ptr<Upgrade> ShinobiTactics::buy() {
    return nextUpgrade->clone();
}