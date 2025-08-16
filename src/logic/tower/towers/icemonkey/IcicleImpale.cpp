#include "IcicleImpale.h"
#include "../../../../core/Game.h"

IcicleImpale::IcicleImpale() 
    : Upgrade("Icile Impale", 150, "Larger freeze area.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Icile Impale";
}

IcicleImpale::IcicleImpale(const IcicleImpale& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> IcicleImpale::clone() const {
    return std::make_unique<IcicleImpale>(*this);
}

void IcicleImpale::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/IcicleImpaleUpgradeIcon.png");
}

void IcicleImpale::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.extraMoabDebuff.bonusDamage += 40;
    attackBuff.cooldownRatio *= 2.0f / 3.0f;
    attackBuff.extraNormalDebuff += BloonDebuff().getIFreeze(1.5f);
    attackBuff.extraMoabDebuff += BloonDebuff().getIFreeze(1.5f);
}

std::unique_ptr<Upgrade> IcicleImpale::buy() {
    return nextUpgrade->clone();
}