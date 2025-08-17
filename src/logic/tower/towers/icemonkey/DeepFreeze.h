#ifndef DEEP_FREEZE_H
#define DEEP_FREEZE_H

#include "../../Upgrade.h"

class DeepFreeze : public Upgrade {
public:
    DeepFreeze();
    DeepFreeze(const DeepFreeze& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~DeepFreeze() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // DEEP_FREEZE_H