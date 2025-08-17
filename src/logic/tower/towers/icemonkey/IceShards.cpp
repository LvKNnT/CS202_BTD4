#include "IceShards.h"
#include "../../../../core/Game.h"

#include "Embrittlement.h"

IceShards::IceShards() 
    : Upgrade("IceShards", 1500, "Removes Camo and Regrow properties when damaging Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Embrittlement>(); // Temporary lmao
    tag = "IceShards";
}

IceShards::IceShards(const IceShards& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> IceShards::clone() const {
    return std::make_unique<IceShards>(*this);
}

void IceShards::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/IceShardsUpgradeIcon.png");
}

void IceShards::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canStripCamo = true;
    attackBuff.properties.canStripRegrow = true;
}

std::unique_ptr<Upgrade> IceShards::buy() {
    return nextUpgrade->clone();
}