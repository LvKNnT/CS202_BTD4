#include "DeepFreeze.h"
#include "../../../../core/Game.h"

#include "ArcticWind.h"

DeepFreeze::DeepFreeze() 
    : Upgrade("Deep Freeze", 300, "Attacks faster and freezes for longer.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<ArcticWind>(); // Temporary lmao
    tag = "Deep Freeze";
}

DeepFreeze::DeepFreeze(const DeepFreeze& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> DeepFreeze::clone() const {
    return std::make_unique<DeepFreeze>(*this);
}

void DeepFreeze::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ice_Monkey/DeepFreezeUpgradeIcon.png");
}

void DeepFreeze::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.extraNormalDebuff += BloonDebuff().getIFreeze(2.2f);
    attackBuff.pierce += 5;
}

std::unique_ptr<Upgrade> DeepFreeze::buy() {
    return nextUpgrade->clone();
}