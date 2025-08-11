#ifndef LONG_RANGE_DARTS_H
#define LONG_RANGE_DARTS_H

#include "../../Upgrade.h"

class LongRangeDarts : public Upgrade {
public:
    LongRangeDarts();
    LongRangeDarts(const LongRangeDarts& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~LongRangeDarts() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // LONG_RANGE_DARTS_H