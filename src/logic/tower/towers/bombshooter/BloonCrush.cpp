#include "BloonCrush.h"
#include "../../../../core/Game.h"

BloonCrush::BloonCrush() 
    : Upgrade("Bloon Crush", 55000, "Bloon shattering explosions do massive damage and can stun MOAB-Class bloons.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Bloon Crush";
}

BloonCrush::BloonCrush(const BloonCrush& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BloonCrush::clone() const {
    return std::make_unique<BloonCrush>(*this);
}

void BloonCrush::loadTexture() {
    // Load the texture for Bloon Crush upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/BloonCrushUpgradeIcon.png");
}

void BloonCrush::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) {
    for (auto& attack : attacks) {
        if (attack->getTag() == "ReallyBigBombsAttack") {
            attack->setDamage(24);
            attack->getProperties() += BulletProperties{true, true, true, true, false, true}; // canHitLead, canHitBlack, canHitWhite, canHitFrozen, canHitCamo, canHitPurple.
            attack->getNormalDebuff() += BloonDebuff().getIStun(2.0f);
            attack->getMoabDebuff() += BloonDebuff().getIStun(2.0f);
            attack->getMoabDebuff() += BloonDebuff().getIKnockBack(0.1f, 1.5f); 
        }
    }
}

std::unique_ptr<Upgrade> BloonCrush::buy() {
    return nextUpgrade->clone();
}
