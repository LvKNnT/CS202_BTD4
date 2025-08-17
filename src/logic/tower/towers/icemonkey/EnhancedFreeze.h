#ifndef ENHACED_FREEZE_H
#define ENHACED_FREEZE_H

#include "../../Upgrade.h"

class EnhancedFreeze : public Upgrade {
public:
    EnhancedFreeze();
    EnhancedFreeze(const EnhancedFreeze& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~EnhancedFreeze() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ENHACED_FREEZE_H