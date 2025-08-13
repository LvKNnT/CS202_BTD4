#ifndef FAST_FIRING_H
#define FAST_FIRING_H

#include "../../Upgrade.h"

class FastFiring : public Upgrade {
public:
    FastFiring();
    FastFiring(const FastFiring& other);
    ~FastFiring() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // FAST_FIRING_H