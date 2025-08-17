#ifndef CRYO_CANNON_H
#define CRYO_CANNON_H

#include "../../Upgrade.h"

class CryoCannon : public Upgrade {
public:
    CryoCannon();
    CryoCannon(const CryoCannon& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~CryoCannon() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // CRYO_CANNON_H