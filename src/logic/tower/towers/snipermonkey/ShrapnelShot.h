#ifndef SHRAPNEL_SHOT_H
#define SHRAPNEL_SHOT_H

#include "../../Upgrade.h"

class ShrapnelShot : public Upgrade {
public:
    ShrapnelShot();
    ShrapnelShot(const ShrapnelShot& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~ShrapnelShot() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SHRAPNEL_SHOT_H