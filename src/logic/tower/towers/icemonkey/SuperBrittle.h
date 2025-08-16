#ifndef SUPER_BRITTLE_H
#define SUPER_BRITTLE_H

#include "../../Upgrade.h"

class SuperBrittle : public Upgrade {
public:
    SuperBrittle();
    SuperBrittle(const SuperBrittle& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~SuperBrittle() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SUPER_BRITTLE_H