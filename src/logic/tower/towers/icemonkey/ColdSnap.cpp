#include "ColdSnap.h"
#include "../../../../core/Game.h"

#include "IceShards.h"

ColdSnap::ColdSnap() 
    : Upgrade("Cold Snap", 350, "Can freeze and pop Lead Bloons and Camo Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<IceShards>(); // Temporary lmao
    tag = "Cold Snap";
}

ColdSnap::ColdSnap(const ColdSnap& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ColdSnap::clone() const {
    return std::make_unique<ColdSnap>(*this);
}

void ColdSnap::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/MetalFreezeUpgradeIcon.png");
}

void ColdSnap::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canLead = true;
    attackBuff.properties.canCamo = true;
}

std::unique_ptr<Upgrade> ColdSnap::buy() {
    return nextUpgrade->clone();
}