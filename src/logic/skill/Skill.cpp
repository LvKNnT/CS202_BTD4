#include "Skill.h"

#include "../tower/Tower.h"
#include "../enemy/Enemy.h"

Skill::Skill(float cooldown, const std::string& name)
    : cooldown(cooldown), timer(0.0f), name(name) {
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