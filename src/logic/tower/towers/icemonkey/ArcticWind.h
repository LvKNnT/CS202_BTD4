#ifndef ARCTIC_WIND_H
#define ARCTIC_WIND_H

#include "../../Upgrade.h"

class ArcticWind : public Upgrade {
public:
    ArcticWind();
    ArcticWind(const ArcticWind& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~ArcticWind() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ARCTIC_WIND_H