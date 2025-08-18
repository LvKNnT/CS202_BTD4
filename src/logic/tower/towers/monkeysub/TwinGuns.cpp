#include "TwinGuns.h"
#include "../../../../core/Game.h"

#include "AirburstDarts.h"

TwinGuns::TwinGuns() 
    : Upgrade("Twin Guns", 450, "Added twin gun doubles attack speed, and enhances attack speed of other weapons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<AirburstDarts>(); // Temporary lmao
    tag = "Twin Guns";
}

TwinGuns::TwinGuns(const TwinGuns& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> TwinGuns::clone() const {
    return std::make_unique<TwinGuns>(*this);
}

void TwinGuns::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/TwinGunsUpgradeIcon.png");
}

void TwinGuns::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio *= 0.5f; // Reduce cooldown by half
}

std::unique_ptr<Upgrade> TwinGuns::buy() {
    return nextUpgrade->clone();
}