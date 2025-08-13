#include "SeekingShuriken.h"
#include "../../../../core/Game.h"

#include "Caltrops.h"
#include "../../../bullet/bullets/TracingShuriken.h"

SeekingShuriken::SeekingShuriken() 
    : Upgrade("Seeking Shuriken", 300, "Increased attack range and shurikens will seek out and pop Bloons automatically.") {
    // Constructor implementation can be extended if needed
    nextUpgrade = std::make_unique<Caltrops>(); // Temporary lmao
    tag = "Seeking Shuriken";
}

SeekingShuriken::SeekingShuriken(const SeekingShuriken& other)
    : Upgrade(other) {
    // Copy constructor implementation
    nextUpgrade = other.nextUpgrade ? other.nextUpgrade->clone() : nullptr;
}

std::unique_ptr<Upgrade> SeekingShuriken::clone() const {
    return std::make_unique<SeekingShuriken>(*this);
}

void SeekingShuriken::loadTexture() {
    // Load the texture for Sharp Shots upgrade
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/tower/Ninja_Monkey/SeekingShurikenUpgradeIcon.png");
}

void SeekingShuriken::update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) {
    attackBuff.range += 7;
    
    
    for(auto& attack : attacks) {
        if(attack->getTag() == "Grandmaster Ninja") continue;
        
        if(attack->getTag() == "ShurikenAttack") {
            attack->getProperties().getITracing(200.0f, TargetPriority::First);
        }
    }
}

std::unique_ptr<Upgrade> SeekingShuriken::buy() {
    return nextUpgrade->clone();
}