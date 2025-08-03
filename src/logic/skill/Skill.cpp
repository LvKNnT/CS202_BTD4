#include "Skill.h"

#include "../tower/Tower.h"
#include "../enemy/Enemy.h"

Skill::Skill(float cooldown, const std::string& name)
    : cooldown(cooldown), timer(0.0f), name(name) {
}
Skill::~Skill() {
    // Destructor implementation can be extended if needed
}