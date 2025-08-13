#include "CrippleMOAB.h"
#include "../../../../core/Game.h"

CrippleMOAB::CrippleMOAB() 
    : Upgrade("Cripple MOAB", 32000, "Crippled MOABs are immobilized for longer and take extra damage from all other attacks.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // No further upgrade available
    tag = "Cripple MOAB";
}

CrippleMOAB::CrippleMOAB(const CrippleMOAB& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> CrippleMOAB::clone() const {
    return std::make_unique<CrippleMOAB>(*this);
}

void CrippleMOAB::loadTexture() {
    // Load the texture for Cripple MOAB upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/CrippleMOABUpgradeIcon.png");
}

void CrippleMOAB::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 110; // Increase damage to MOAB-class Bloons
    attackBuff.extraMoabDebuff += BloonDebuff().getIStun(4.0f); // Slow down MOAB-class Bloons
    attackBuff.extraMoabDebuff.bonusOnHitDamage += 5; // Add bonus damage on hit to MOAB-class Bloons
}

std::unique_ptr<Upgrade> CrippleMOAB::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}