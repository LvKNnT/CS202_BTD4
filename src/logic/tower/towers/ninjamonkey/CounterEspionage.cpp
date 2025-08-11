#include "CounterEspionage.h"
#include "../../../../core/Game.h"

#include "ShinobiTactics.h"

CounterEspionage::CounterEspionage() 
    : Upgrade("Counter Espionage", 400, "Ninja attacks can strip camo from Bloons they damage.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ShinobiTactics>(); // Temporary lmao
    tag = "Counter Espionage";
}

CounterEspionage::CounterEspionage(const CounterEspionage& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> CounterEspionage::clone() const {
    return std::make_unique<CounterEspionage>(*this);
}

void CounterEspionage::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/CounterEspionageUpgradeIcon.png");
}

void CounterEspionage::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    for(auto& attack : attacks) {
        // Ninja attacks can strip camo from Bloons they damage.
        attackBuff.properties.canStripCamo = true;
        attackBuff.extraNormalDebuff.bonusCamoDamage += 2;
    }
}

std::unique_ptr<Upgrade> CounterEspionage::buy() {
    return nextUpgrade->clone();
}