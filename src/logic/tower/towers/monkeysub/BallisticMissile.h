#ifndef BALLISTIC_MISSILE_H
#define BALLISTIC_MISSILE_H

#include "../../Upgrade.h"

class BallisticMissile : public Upgrade {
public:
    BallisticMissile();
    BallisticMissile(const BallisticMissile& other);
    ~BallisticMissile() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // BALLISTIC_MISSILE_H