#include "FlashBomb.h"
#include "../../../../core/Game.h"
#include "../../../attack/attacks/FlashBombAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "StickyBomb.h"

FlashBomb::FlashBomb() 
    : Upgrade("Flash Bomb", 2250, "Combination attack! Alternates flash bombs that stun many Bloons and shuriken deal increased damage to stunned targets.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<StickyBomb>(); // Temporary lmao
    tag = "Flash Bomb";
}

FlashBomb::FlashBomb(const FlashBomb& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> FlashBomb::clone() const {
    return std::make_unique<FlashBomb>(*this);
}

void FlashBomb::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/FlashBombUpgradeIcon.png");
}

void FlashBomb::update(std::vector<std::unique_ptr<Attack>> &attacks, AttackBuff &attackBuff, std::unique_ptr<Skill> &skill, std::vector<std::unique_ptr<Skill>> &passiveSkills, MapManager &mapManager, ResourceManager &resourceManager) {
    attacks.push_back(std::make_unique<FlashBombAttack>(attacks[0]->getRange(), 2.48f, attacks[0]->getPosition(), attacks[0]->getTowerId(), 3, attacks[0]->getSpeed(), 30, 0.25f, BulletProperties::normal(), attackBuff.extraNormalDebuff, attackBuff.extraMoabDebuff));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>());
    attacks.back()->getProperties() += BulletProperties{true, true, true, true, false, true}; // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
    attacks.back()->getNormalDebuff() += BloonDebuff().getIStun(1.3f);
    if(attacks[0]->getNormalDebuff().knockbackChance == 15) {
        // Flash Bomb has 30% of knockback
        attacks.back()->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 30);
    }
}

std::unique_ptr<Upgrade> FlashBomb::buy() {
    return nextUpgrade->clone();
}