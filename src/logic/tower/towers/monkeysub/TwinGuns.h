#ifndef TWIN_GUNS_H
#define TWIN_GUNS_H

#include "../../Upgrade.h"

class TwinGuns : public Upgrade {
public:
    TwinGuns();
    TwinGuns(const TwinGuns& other);
    ~TwinGuns() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // TWIN_GUNS_H