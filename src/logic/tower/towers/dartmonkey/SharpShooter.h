#ifndef SHARP_SHOOTER_H
#define SHARP_SHOOTER_H

#include "../../Upgrade.h"

class SharpShooter : public Upgrade {
public:
    SharpShooter();
    SharpShooter(const SharpShooter& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~SharpShooter() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SHARP_SHOOTER_H