#include "StickyBomb.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/StickyBombAttack.h"
#include "../../../attack/patterns/NormalAttack.h"
#include "MasterBomber.h"

StickyBomb::StickyBomb() 
    : Upgrade("Sticky Bomb", 5000, "Throws powerful timed charges at MOAB-Class Bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<MasterBomber>(); // Temporary lmao
    tag = "Sticky Bomb";
}

StickyBomb::StickyBomb(const StickyBomb& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> StickyBomb::clone() const {
    return std::make_unique<StickyBomb>(*this);
}

void StickyBomb::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/StickyBombUpgradeIcon.png");
}

void StickyBomb::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    attacks.push_back(std::make_unique<StickyBombAttack>(attacks[0]->getRange(), 4.5f, attacks[0]->getPosition(), attacks[0]->getTowerId(), 0, attacks[0]->getSpeed(), 11, 3.0f, BulletProperties::normal(), attackBuff.extraNormalDebuff, attackBuff.extraMoabDebuff));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>());
    attacks.back()->getProperties().getITracing(2000.0f, TargetPriority::Strong);
    attacks.back()->getProperties() += BulletProperties{true, true, true, true, false, true}; // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
    if(attacks[0]->getNormalDebuff().knockbackChance == 15) {
        // Sticky Bomb has 15% of knockback
        attacks.back()->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 15);
    }
}

std::unique_ptr<Upgrade> StickyBomb::buy() {
    return nextUpgrade->clone();
}