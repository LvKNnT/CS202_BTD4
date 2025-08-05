#include "SuperMonkeyFanClubUpgrade.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/SuperMonkeyFanClubSkill.h"

#include "PlasmaMonkeyFanClubUpgrade.h"

SuperMonkeyFanClubUpgrade::SuperMonkeyFanClubUpgrade()
    : Upgrade("Super Monkey Fan Club", 7200, "Super Monkey Fan Club Ability: Converts up to 10 nearby Dart Monkeys including itself into Super Monkeys for 15 seconds. Regular attack speed also increased.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<PlasmaMonkeyFanClubUpgrade>(); // Temporary lmao
    tag = "Super Monkey Fan Club";
}

SuperMonkeyFanClubUpgrade::SuperMonkeyFanClubUpgrade(const SuperMonkeyFanClubUpgrade& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SuperMonkeyFanClubUpgrade::clone() const {
    return std::make_unique<SuperMonkeyFanClubUpgrade>(*this);
}

void SuperMonkeyFanClubUpgrade::loadTexture() {
    // Load the texture for Super Monkey Fan Club upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Dart_Monkey/SuperMonkeyFanClubUpgradeIcon.png");
    Game::Instance().getTextureManager().loadTexture("Super Monkey Fan Club Dart", "../assets/tower/Dart_Monkey/Super_Monkey.png");
}

void SuperMonkeyFanClubUpgrade::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    attackBuff.cooldownRatio *= 0.5f;
    skill = std::make_unique<SuperMonkeyFanClubSkill>();
}

std::unique_ptr<Upgrade> SuperMonkeyFanClubUpgrade::buy() {
    return nextUpgrade->clone(); // Return the next upgrade
}