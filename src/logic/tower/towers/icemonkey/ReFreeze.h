#ifndef RE_FREEZE_H
#define RE_FREEZE_H

#include "../../Upgrade.h"

class ReFreeze : public Upgrade {
public:
    ReFreeze();
    ReFreeze(const ReFreeze& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~ReFreeze() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // RE_FREEZE_H