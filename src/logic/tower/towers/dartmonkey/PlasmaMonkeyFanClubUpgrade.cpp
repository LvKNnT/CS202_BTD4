#include "PlasmaMonkeyFanClubUpgrade.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/PlasmaMonkeyFanClubSkill.h"

PlasmaMonkeyFanClubUpgrade::PlasmaMonkeyFanClubUpgrade()
    : Upgrade("Plasma Monkey Fan Club", 45000, "Elite membership of this club grants the Dart Monkeys even more power.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Upgrade>(); // Temporary lmao
    tag = "Plasma Monkey Fan Club";
}

PlasmaMonkeyFanClubUpgrade::PlasmaMonkeyFanClubUpgrade(const PlasmaMonkeyFanClubUpgrade& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> PlasmaMonkeyFanClubUpgrade::clone() const {
    return std::make_unique<PlasmaMonkeyFanClubUpgrade>(*this);
}

void PlasmaMonkeyFanClubUpgrade::loadTexture() {
    // Load the texture for Plasma Monkey Fan Club upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/PMFCUpgradeIcon.png");
    Game::Instance().getTextureManager().loadTexture("Plasma Monkey Fan Club Dart", "../assets/tower/Dart_Monkey/Super_Monkey.png");
}

void PlasmaMonkeyFanClubUpgrade::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.cooldownRatio /= 0.5f;
    skill = std::make_unique<PlasmaMonkeyFanClubSkill>();
}

std::unique_ptr<Upgrade> PlasmaMonkeyFanClubUpgrade::buy() {
    return nextUpgrade->clone(); // Return the next upgrade
}