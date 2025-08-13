#ifndef ELITE_SNIPER_H
#define ELITE_SNIPER_H

#include "../../Upgrade.h"

class EliteSniper : public Upgrade {
public:
    EliteSniper();
    EliteSniper(const EliteSniper& other);
    ~EliteSniper() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ELITE_SNIPER_Hd