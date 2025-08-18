#include "SubmergeAndSupport.h"
#include "../../../../core/Game.h"

#include "../../../attack/attacks/SubmergeAttack.h"
#include "../../../attack/patterns/NormalAttack.h"

#include "BloontoniumReactor.h"

SubmergeAndSupport::SubmergeAndSupport() 
    : Upgrade("Submerge and Support", 700, "Permanently reveals Camo bloons in its radius.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<BloontoniumReactor>(); // Temporary lmao
    tag = "Submerge and Support";
}

SubmergeAndSupport::SubmergeAndSupport(const SubmergeAndSupport& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SubmergeAndSupport::clone() const {
    return std::make_unique<SubmergeAndSupport>(*this);
}

void SubmergeAndSupport::loadTexture() {
    // Load the texture for Bloon Sabotage upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Monkey_Sub/SubmergeandSupportUpgradeIcon.png");
}

void SubmergeAndSupport::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attacks.push_back(std::make_unique<SubmergeAttack>(
        attacks.back()->getRange(), 
        1.5f, 
        attacks.back()->getPosition(),
        attacks.back()->getTowerId(),
        0, 
        0, // speed
        100, // pierce
        0.1f, // lifeSpan
        BulletProperties{            
            true, // canLead
            true, // canBlack
            true, // canWhite
            true, // canFrozen
            true,  // canCamo
            true, // canPurple
            true // canStripCamo
        }, 
        BloonDebuff(), 
        BloonDebuff()
    ));
    attacks.back()->setAttackPattern(std::make_unique<NormalAttack>());
}

std::unique_ptr<Upgrade> SubmergeAndSupport::buy() {
    return nextUpgrade->clone();
}