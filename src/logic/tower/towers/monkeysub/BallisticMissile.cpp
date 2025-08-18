#include "BallisticMissile.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/BallisticAttack.h"
#include "../../../attack/patterns/NormalAttack.h"

#include "FirstStrikeCapability.h"

BallisticMissile::BallisticMissile() 
    : Upgrade("Ballistic Missile", 1350, "Missile seeks target within range and does extra MOAB and Ceramic damage.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<FirstStrikeCapability>(); // Temporary lmao
    tag = "Ballistic Missile";
}

BallisticMissile::BallisticMissile(const BallisticMissile& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BallisticMissile::clone() const {
    return std::make_unique<BallisticMissile>(*this);
}

void BallisticMissile::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/BallisticMissileUpgradeIcon.png");
}

void BallisticMissile::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 16.0f;
    attackBuff.extraNormalDebuff.bonusDamage += 3;
    attackBuff.extraMoabDebuff.bonusDamage += 3;
    
    attacks.push_back(std::make_unique<BallisticAttack>(
        attacks.back()->getRange(), 
        1.0f, 
        attacks.back()->getPosition(),
        attacks.back()->getTowerId(),
        3, // damage
        600, // speed
        40, // pierce
        2.0f, // lifeSpan
        BulletProperties::bomb().getITracing(100.0f, TargetPriority::First, true),
        BloonDebuff(),
        BloonDebuff()
    ));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>());
}

std::unique_ptr<Upgrade> BallisticMissile::buy() {
    return nextUpgrade->clone();
}