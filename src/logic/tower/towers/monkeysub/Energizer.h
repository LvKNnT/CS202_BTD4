#ifndef ENERGIZER_H
#define ENERGIZER_H

#include "../../Upgrade.h"

class Energizer : public Upgrade {
public:
    Energizer();
    Energizer(const Energizer& other);
    ~Energizer() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ENERGIZER_H