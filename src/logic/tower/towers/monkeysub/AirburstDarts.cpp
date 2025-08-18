#include "AirburstDarts.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/AirburstAttack.h"

#include "TripleGuns.h"

AirburstDarts::AirburstDarts() 
    : Upgrade("Airburst Darts", 1000, "Airburst darts split into 3 on impact for massively increased popping power.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<TripleGuns>(); // Temporary lmao
    tag = "Airburst Darts";
}

AirburstDarts::AirburstDarts(const AirburstDarts& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> AirburstDarts::clone() const {
    return std::make_unique<AirburstDarts>(*this);
}

void AirburstDarts::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/AirburstDartsUpgradeIcon.png");
}

void AirburstDarts::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto& attack : attacks) {
        if(attack->getTag() == "SubAttack") {
            std::unique_ptr<AttackPattern> attackPattern = std::move(attack->getAttackPattern());
            attack = std::make_unique<AirburstAttack>(
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

std::unique_ptr<Upgrade> AirburstDarts::buy() {
    return nextUpgrade->clone();
}