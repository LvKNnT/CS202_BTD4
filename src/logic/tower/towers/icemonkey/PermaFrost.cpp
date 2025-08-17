#include "PermaFrost.h"
#include "../../../../core/Game.h"

#include "ColdSnap.h"

PermaFrost::PermaFrost() 
    : Upgrade("Permafrost", 150, "Bloons move slowly even after thawing out.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ColdSnap>(); // Temporary lmao
    tag = "Permafrost";
}

PermaFrost::PermaFrost(const PermaFrost& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> PermaFrost::clone() const {
    return std::make_unique<PermaFrost>(*this);
}

void PermaFrost::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/PermafrostUpgradeIcon.png");
}

void PermaFrost::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.extraNormalDebuff += BloonDebuff().getISlow(0.25, 10);
}

std::unique_ptr<Upgrade> PermaFrost::buy() {
    return nextUpgrade->clone();
}