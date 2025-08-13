#ifndef ELITE_DEFENDER_H
#define ELITE_DEFENDER_H

#include "../../Upgrade.h"

class EliteDefender : public Upgrade {
public:
    EliteDefender();
    EliteDefender(const EliteDefender& other);
    ~EliteDefender() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ELITE_DEFENDER_H