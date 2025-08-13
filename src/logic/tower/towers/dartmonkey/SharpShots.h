#ifndef SHARP_SHOTS_H
#define SHARP_SHOTS_H

#include "../../Upgrade.h"

class SharpShots : public Upgrade {
public:
    SharpShots();
    SharpShots(const SharpShots& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~SharpShots() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // SHARP_SHOTS_H