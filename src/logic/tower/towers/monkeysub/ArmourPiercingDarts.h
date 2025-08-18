#ifndef ARMOUR_PIERCING_DARTS_H
#define ARMOUR_PIERCING_DARTS_H

#include "../../Upgrade.h"

class ArmourPiercingDarts : public Upgrade {
public:
    ArmourPiercingDarts();
    ArmourPiercingDarts(const ArmourPiercingDarts& other);
    ~ArmourPiercingDarts() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ARMOUR_PIERCING_DARTS_H