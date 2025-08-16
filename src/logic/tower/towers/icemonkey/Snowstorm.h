#ifndef SNOWSTORM_H
#define SNOWSTORM_H

#include "../../Upgrade.h"

class Snowstorm : public Upgrade {
public:
    Snowstorm();
    Snowstorm(const Snowstorm& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~Snowstorm() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SNOWSTORM_H