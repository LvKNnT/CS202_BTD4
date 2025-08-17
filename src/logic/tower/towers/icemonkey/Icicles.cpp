#include "Icicles.h"
#include "../../../../core/Game.h"

#include "IcicleImpale.h"

Icicles::Icicles() 
    : Upgrade("Icicles", 2750, "Does bonus damage to MOAB-Class Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<IcicleImpale>(); // Temporary lmao
    tag = "Icicles";
}

Icicles::Icicles(const Icicles& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Icicles::clone() const {
    return std::make_unique<Icicles>(*this);
}

void Icicles::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/IciclesUpgradeIcon.png");
}

void Icicles::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 4;
    attackBuff.cooldownRatio *= 0.4f;
    attackBuff.extraMoabDebuff.bonusDamage += 8;
}

std::unique_ptr<Upgrade> Icicles::buy() {
    return nextUpgrade->clone();
}