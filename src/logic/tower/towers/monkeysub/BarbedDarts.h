#ifndef BARBED_DARTS_H
#define BARBED_DARTS_H

#include "../../Upgrade.h"

class BarbedDarts : public Upgrade {
public:
    BarbedDarts();
    BarbedDarts(const BarbedDarts& other);
    ~BarbedDarts() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // BARBED_DARTS_H