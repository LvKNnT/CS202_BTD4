#include "BloonImpact.h"
#include "../../../../core/Game.h"

#include "BloonCrush.h"

BloonImpact::BloonImpact() 
    : Upgrade("Bloon Impact", 3200, "Explosions become so violent Bloons are stunned for a short time when they are hit. Range is increased and frags are even more effective.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<BloonCrush>(); // Temporary lmao
    tag = "Bloon Impact";
}

BloonImpact::BloonImpact(const BloonImpact& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BloonImpact::clone() const {
    return std::make_unique<BloonImpact>(*this);
}

void BloonImpact::loadTexture() {
    // Load the texture for Bloon Impact upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Boom_Shooter/BloonImpactUpgradeIcon.png");
}

void BloonImpact::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    for (auto& attack : attacks) {
        if (attack->getTag() == "ReallyBigBombsAttack") {
            attack->setDamage(4);
            attack->getNormalDebuff() += BloonDebuff().getIStun(1.4f);
        }
    }
}

std::unique_ptr<Upgrade> BloonImpact::buy() {
    return nextUpgrade->clone();
}