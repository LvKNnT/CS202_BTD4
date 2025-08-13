#include "Caltrops.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/CaltropsAttack.h"
#include "../../../attack/patterns/CaltropsAttackPattern.h"

#include "FlashBomb.h"

Caltrops::Caltrops() 
    : Upgrade("Caltrops", 450, "Throws out spiked caltrops onto the track nearby.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<FlashBomb>(); // Temporary lmao
    tag = "Caltrops";
}

Caltrops::Caltrops(const Caltrops& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> Caltrops::clone() const {
    return std::make_unique<Caltrops>(*this);
}

void Caltrops::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/CaltropsUpgradeIcon.png");
}

void Caltrops::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attacks.push_back(std::make_unique<CaltropsAttack>(attacks[0]->getRange(), 3.9f, attacks[0]->getPosition(), attacks[0]->getTowerId(), 1, 0, 6, 35, BulletProperties::normal(), attackBuff.extraNormalDebuff, attackBuff.extraMoabDebuff));
    attacks.back()->setAttackPattern(std::make_unique<CaltropsAttackPattern>(&mapManager, attacks.back()->getPosition(), attacks.back()->getRange()));
    if(attacks[0]->getNormalDebuff().knockbackChance == 15) {
        // Caltrops only has 10% of knockback
        attacks.back()->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 10);
    }
}

std::unique_ptr<Upgrade> Caltrops::buy() {
    return nextUpgrade->clone();
}