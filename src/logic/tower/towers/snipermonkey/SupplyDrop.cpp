#include "SupplyDrop.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/SupplyDropSkill.h"

#include "EliteSniper.h"

SupplyDrop::SupplyDrop() 
    : Upgrade("Supply Drop", 1100, "Drops a supply crate with cash.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<EliteSniper>(); // No further upgrade available
    tag = "Supply Drop";
}

SupplyDrop::SupplyDrop(const SupplyDrop& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SupplyDrop::clone() const {
    return std::make_unique<SupplyDrop>(*this);
}

void SupplyDrop::loadTexture() {
    // Load the texture for Supply Drop upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Sniper_Monkey/CashDropUpgradeIcon.png");
}

void SupplyDrop::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.pierce += 2;
    attackBuff.properties.canLead = true; // Allow bullets to hit Lead bloons
    attackBuff.properties.canFrozen = true; // Allow bullets to hit Frozen bloons
    
    skill = std::make_unique<SupplyDropSkill>();
}

std::unique_ptr<Upgrade> SupplyDrop::buy() {
    return nextUpgrade ? nextUpgrade->clone() : nullptr; // No further upgrade available
}