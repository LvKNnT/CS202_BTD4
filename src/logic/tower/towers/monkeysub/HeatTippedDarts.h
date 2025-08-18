#ifndef HEAT_TIPPED_DARTS_H
#define HEAT_TIPPED_DARTS_H

#include "../../Upgrade.h"

class HeatTippedDarts : public Upgrade {
public:
    HeatTippedDarts();
    HeatTippedDarts(const HeatTippedDarts& other);
    ~HeatTippedDarts() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // HEAT_TIPPED_DARTS_H