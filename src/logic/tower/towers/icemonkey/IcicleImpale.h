#ifndef ICICLE_IMPALE_H
#define ICICLE_IMPALE_H

#include "../../Upgrade.h"

class IcicleImpale : public Upgrade {
public:
    IcicleImpale();
    IcicleImpale(const IcicleImpale& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~IcicleImpale() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ICICLE_IMPALE_H