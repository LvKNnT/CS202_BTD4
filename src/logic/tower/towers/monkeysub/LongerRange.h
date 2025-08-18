#ifndef LONGER_RANGE_H
#define LONGER_RANGE_H

#include "../../Upgrade.h"

class LongerRange : public Upgrade {
public:
    LongerRange();
    LongerRange(const LongerRange& other);
    ~LongerRange() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // LONGER_RANGE_H