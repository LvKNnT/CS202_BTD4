#ifndef COLD_SNAP_H
#define COLD_SNAP_H

#include "../../Upgrade.h"

class ColdSnap : public Upgrade {
public:
    ColdSnap();
    ColdSnap(const ColdSnap& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~ColdSnap() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // COLD_SNAP_H