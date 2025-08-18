#include "TripleGuns.h"
#include "../../../../core/Game.h"

#include "ArmourPiercingDarts.h"

TripleGuns::TripleGuns() 
    : Upgrade("Triple Guns", 1100, "Adds a third gun for even faster firing.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ArmourPiercingDarts>(); // Temporary lmao
    tag = "Triple Guns";
}

TripleGuns::TripleGuns(const TripleGuns& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> TripleGuns::clone() const {
    return std::make_unique<TripleGuns>(*this);
}

void TripleGuns::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/TripleGunsUpgradeIcon.png");
}

void TripleGuns::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 2.0f / 3.0f; // Reduce cooldown by half
}

std::unique_ptr<Upgrade> TripleGuns::buy() {
    return nextUpgrade->clone();
}