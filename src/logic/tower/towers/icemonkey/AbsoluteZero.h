#ifndef ABSOLUTE_ZERO_H
#define ABSOLUTE_ZERO_H

#include "../../Upgrade.h"

class AbsoluteZero : public Upgrade {
public:
    AbsoluteZero();
    AbsoluteZero(const AbsoluteZero& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~AbsoluteZero() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ABSOLUTE_ZERO_H