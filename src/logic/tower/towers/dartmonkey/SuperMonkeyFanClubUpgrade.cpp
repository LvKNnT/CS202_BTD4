#include "SuperMonkeyFanClubUpgrade.h"
#include "../../../../core/Game.h"

#include "../../../skill/skills/SuperMonkeyFanClubSkill.h"

#include "PlasmaMonkeyFanClubUpgrade.h"

SuperMonkeyFanClubUpgrade::SuperMonkeyFanClubUpgrade()
    : Upgrade("Super Monkey Fan Club", 5000, "Temporarily transforms all nearby Dart Monkeys into Super Monkeys.") {
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
}

void SuperMonkeyFanClubUpgrade::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) {
    attackBuff.cooldownRatio *= 0.5f;
    skill = std::make_unique<SuperMonkeyFanClubSkill>();
}

std::unique_ptr<Upgrade> SuperMonkeyFanClubUpgrade::buy() {
    return nextUpgrade->clone(); // Return the next upgrade
}