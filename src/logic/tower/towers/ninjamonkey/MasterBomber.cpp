#include "MasterBomber.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/MasterBomberAttack.h"
#include "../../../attack/patterns/NormalAttack.h"

MasterBomber::MasterBomber() 
    : Upgrade("Master Bomber", 40000, "One Monkey MOAB demolition machine.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Master Bomber";
}

MasterBomber::MasterBomber(const MasterBomber& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> MasterBomber::clone() const {
    return std::make_unique<MasterBomber>(*this);
}

void MasterBomber::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/MasterBomberUpgradeIcon.png");
}

void MasterBomber::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.properties.canCamo = true;
    

    for(auto &attack:attacks) {
        if(attack->getTag() == "StickyBombAttack") {
            auto newStickyBombAttack = std::make_unique<MasterBomberAttack>(attacks[0]->getRange(), 2.25f, attacks[0]->getPosition(), attacks[0]->getTowerId(), 3000, attacks[0]->getSpeed(), 1, 3.0, BulletProperties::normal(), attackBuff.extraNormalDebuff, attackBuff.extraMoabDebuff);
            newStickyBombAttack->setAttackPattern(std::make_unique<NormalAttack>());
            newStickyBombAttack->getProperties() += BulletProperties{true, true, true, true, false, true}; // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
            newStickyBombAttack->getMoabDebuff() += BloonDebuff().getIStun(1.0f);
            if(attacks[0]->getNormalDebuff().knockbackChance == 15) {
                // Sticky Bomb has 15% of knockback
                newStickyBombAttack->getNormalDebuff() += BloonDebuff().getIKnockBack(1.0f, 2.0f, 15);
            }

            attack = std::move(newStickyBombAttack);
        } else if(attack->getTag() == "FlashBombAttack") {
            attack->setDamage(10);
            attack->getMoabDebuff() += BloonDebuff().getIStun(0.325f);
            attack->getNormalDebuff() += BloonDebuff().getIStun(1.3f);
        } else if(attack->getTag() == "CaltropsAttack") {
            attack->setDamage(5);
            attack->getNormalDebuff() += BloonDebuff().getIBonusDamage(0, 0, 0, 5); // + 5 damage for ceramics
        } else if(attack->getTag() == "ShurikenAttack") {
            attack->getNormalDebuff() += BloonDebuff().getIOnHitDamage(19);
        } 
    }
}

std::unique_ptr<Upgrade> MasterBomber::buy() {
    return nextUpgrade->clone();
}