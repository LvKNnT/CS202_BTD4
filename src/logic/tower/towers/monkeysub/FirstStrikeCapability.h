#ifndef FIRST_STRIKE_CAPABILITY_H
#define FIRST_STRIKE_CAPABILITY_H

#include "../../Upgrade.h"

class FirstStrikeCapability : public Upgrade {
public:
    FirstStrikeCapability();
    FirstStrikeCapability(const FirstStrikeCapability& other);
    ~FirstStrikeCapability() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // FIRST_STRIKE_CAPABILITY_H