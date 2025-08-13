#ifndef DEADLY_PRECISION_H
#define DEADLY_PRECISION_H

#include "../../Upgrade.h"

class DeadlyPrecision : public Upgrade {
public:
    DeadlyPrecision();
    DeadlyPrecision(const DeadlyPrecision& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~DeadlyPrecision() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // DEADLY_PRECISION_H