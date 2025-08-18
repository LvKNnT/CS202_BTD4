#include "ArmourPiercingDarts.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/ArmourPiercingAttack.h"

#include "SubCommander.h"

ArmourPiercingDarts::ArmourPiercingDarts() 
    : Upgrade("Armor Piercing Darts", 3000, "Special AP darts gain increased damage and popping power, plus additional damage to MOAB class Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<SubCommander>(); // Temporary lmao
    tag = "Armor Piercing Darts";
}

ArmourPiercingDarts::ArmourPiercingDarts(const ArmourPiercingDarts& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> ArmourPiercingDarts::clone() const {
    return std::make_unique<ArmourPiercingDarts>(*this);
}

void ArmourPiercingDarts::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/ArmorPiercingDartsUpgradeIcon.png");
}

void ArmourPiercingDarts::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.damage += 1;
    attackBuff.extraMoabDebuff.bonusDamage += 2;
    attackBuff.pierce += 3;
    
    for(auto& attack : attacks) {
        if(attack->getTag() == "AirburstAttack") {
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<ArmourPiercingAttack>(
                attack->getRange(), 
                attack->getCooldown(), 
                attack->getPosition(),
                attack->getTowerId(),
                attack->getDamage(), 
                attack->getSpeed(), 
                attack->getPierce(), 
                attack->getLifeSpan(),
                attack->getProperties(), 
                attack->getNormalDebuff(), 
                attack->getMoabDebuff()
            );
            attack->setAttackPattern(std::move(attackPattern));
        }
    }
}

std::unique_ptr<Upgrade> ArmourPiercingDarts::buy() {
    return nextUpgrade->clone();
}