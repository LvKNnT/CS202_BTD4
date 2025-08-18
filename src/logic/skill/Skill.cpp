#include "Skill.h"

#include "../tower/Tower.h"
#include "../enemy/Enemy.h"

Skill::Skill(float cooldown, const std::string& name)
    : cooldown(cooldown), timer(0.0f), name(name), isSkillActivating(false) {
}
Skill::~Skill() {
    // Destructor implementation can be extended if needed
}

const std::string& Skill::getName() const {
    return name; // Return the name of the skill
}

float Skill::getCooldownTime() const {
    return cooldown; // Return the cooldown time of the skill
}

float Skill::getTimer() const {
    return timer; // Return the current timer of the skill
}

bool Skill::getISkillsActivating() const {
    return isSkillActivating;
}

void Skill::setCooldown(float newCooldown) {
    cooldown = newCooldown;
}

void Skill::setTimer(float newTimer){
    timer = newTimer;
}

void Skill::setIsSkillActivating(float newIsSkillActivating) {
    isSkillActivating = newIsSkillActivating;
}

