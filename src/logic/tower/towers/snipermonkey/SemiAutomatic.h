#ifndef SEMI_AUTOMATIC_H
#define SEMI_AUTOMATIC_H

#include "../../Upgrade.h"

class SemiAutomatic : public Upgrade {
public:
    SemiAutomatic();
    SemiAutomatic(const SemiAutomatic& other);
    ~SemiAutomatic() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SEMI_AUTOMATIC_H