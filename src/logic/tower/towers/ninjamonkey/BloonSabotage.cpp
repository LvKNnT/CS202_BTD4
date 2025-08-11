#include "BloonSabotage.h"
#include "../../../../core/Game.h"
#include "../../../skill/skills/BloonSabotageSkill.h"
#include "GrandSaboteur.h"

BloonSabotage::BloonSabotage() 
    : Upgrade("Bloon Sabotage", 5200, "Sabotage ability: Lasts 15 seconds. During the sabotage, all Bloons move at half speed.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<GrandSaboteur>(); // Temporary lmao
    tag = "Bloon Sabotage";
}

BloonSabotage::BloonSabotage(const BloonSabotage& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> BloonSabotage::clone() const {
    return std::make_unique<BloonSabotage>(*this);
}

void BloonSabotage::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/BloonSabotageUpgradeIcon.png");
    Game::Instance().getTextureManager().loadTexture("Bloon Sabotage Ninja", "../assets/tower/Ninja_Monkey/BloonSabotageNinja.png");
}

void BloonSabotage::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) {
    skill = std::make_unique<BloonSabotageSkill>();
}

std::unique_ptr<Upgrade> BloonSabotage::buy() {
    return nextUpgrade->clone();
}