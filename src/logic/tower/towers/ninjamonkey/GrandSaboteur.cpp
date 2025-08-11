#include "GrandSaboteur.h"
#include "../../../../core/Game.h"
#include "../../../skill/skills/GrandSaboteurSkill.h"

GrandSaboteur::GrandSaboteur() 
    : Upgrade("Grand Saboteur", 22000, "Ability duration is longer, and MOAB-Class Bloons spawn with less health during the sabotage. Buffs all Shinobi.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Grand Saboteur";
}

GrandSaboteur::GrandSaboteur(const GrandSaboteur& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> GrandSaboteur::clone() const {
    return std::make_unique<GrandSaboteur>(*this);
}

void GrandSaboteur::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/GrandSaboteurUpgradeIcon.png");
    Game::Instance().getTextureManager().loadTexture("Grand Saboteur Ninja", "../assets/tower/Ninja_Monkey/GrandSaboteurNinja.png");
}

void GrandSaboteur::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    skill = std::make_unique<GrandSaboteurSkill>();
}

std::unique_ptr<Upgrade> GrandSaboteur::buy() {
    return nextUpgrade->clone();
}