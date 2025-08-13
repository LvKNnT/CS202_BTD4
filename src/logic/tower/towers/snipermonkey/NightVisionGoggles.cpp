#include "NightVisionGoggles.h"
#include "../../../../core/Game.h"

#include "ShrapnelShot.h"

NightVisionGoggles::NightVisionGoggles() 
    : Upgrade("Night Vision Goggles", 250, "Allows Sniper to detect and do an additional 2 damage to Camo bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ShrapnelShot>(); // No further upgrade available
    tag = "Night Vision Goggles";
}

NightVisionGoggles::NightVisionGoggles(const NightVisionGoggles& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> NightVisionGoggles::clone() const {
    return std::make_unique<NightVisionGoggles>(*this);
}

void NightVisionGoggles::loadTexture() {
    // Load the texture for Night Vision Goggles upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/NightVisionGogglesUpgradeIcon.png");
}

void NightVisionGoggles::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canCamo = true; 
    attackBuff.extraNormalDebuff.bonusCamoDamage += 2; 
    attackBuff.extraMoabDebuff.bonusCamoDamage += 2; 
}

std::unique_ptr<Upgrade> NightVisionGoggles::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}