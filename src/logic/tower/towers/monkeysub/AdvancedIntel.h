#ifndef ADVANCED_INTEL_H
#define ADVANCED_INTEL_H

#include "../../Upgrade.h"

class AdvancedIntel : public Upgrade {
public:
    AdvancedIntel();
    AdvancedIntel(const AdvancedIntel& other);
    ~AdvancedIntel() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ADVANCED_INTEL_H