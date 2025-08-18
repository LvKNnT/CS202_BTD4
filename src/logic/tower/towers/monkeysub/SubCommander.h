#ifndef SUB_COMMANDER_H
#define SUB_COMMANDER_H

#include "../../Upgrade.h"

class SubCommander : public Upgrade {
public:
    SubCommander();
    SubCommander(const SubCommander& other);
    ~SubCommander() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SUB_COMMANDER_H