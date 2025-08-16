#include "Embrittlement.h"
#include "../../../../core/Game.h"

#include "SuperBrittle.h"

Embrittlement::Embrittlement() 
    : Upgrade("Embrittlement", 2300, "All hit Bloons become brittle, take extra damage while frozen, and losing Lead immunity for a short time.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SuperBrittle>(); // Temporary lmao
    tag = "Embrittlement";
}

Embrittlement::Embrittlement(const Embrittlement& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Embrittlement::clone() const {
    return std::make_unique<Embrittlement>(*this);
}

void Embrittlement::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/EmbrittlementUpgradeIcon.png");
}

void Embrittlement::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canEmbrittle = true; // Enable embrittlement effect
    attackBuff.extraNormalDebuff.bonusOnHitDamage += 1;
}

std::unique_ptr<Upgrade> Embrittlement::buy() {
    return nextUpgrade->clone();
}