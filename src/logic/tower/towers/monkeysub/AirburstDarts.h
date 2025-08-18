#ifndef AIRBURST_DARTS_H
#define AIRBURST_DARTS_H

#include "../../Upgrade.h"

class AirburstDarts : public Upgrade {
public:
    AirburstDarts();
    AirburstDarts(const AirburstDarts& other);
    ~AirburstDarts() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // AIRBURST_DARTS_H