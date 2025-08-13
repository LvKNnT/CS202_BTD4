#include "MaimMOAB.h"
#include "../../../../core/Game.h"

#include "CrippleMOAB.h"

MaimMOAB::MaimMOAB() 
    : Upgrade("Maim MOAB", 6000, "Deals much more damage and immobilizes MOAB class bloons for a short time.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<CrippleMOAB>(); // No further upgrade available
    tag = "Maim MOAB";
}

MaimMOAB::MaimMOAB(const MaimMOAB& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MaimMOAB::clone() const {
    return std::make_unique<MaimMOAB>(*this);
}

void MaimMOAB::loadTexture() {
    // Load the texture for Main MOAB upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/MaimMOABUpgradeIcon.png");
}

void MaimMOAB::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 10; // Increase damage to MOAB-class Bloons
    attackBuff.extraMoabDebuff += BloonDebuff().getIStun(3.0f);
}

std::unique_ptr<Upgrade> MaimMOAB::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}