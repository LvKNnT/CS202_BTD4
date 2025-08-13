#ifndef EXTRA_RANGE_H
#define EXTRA_RANGE_H

#include "../../Upgrade.h"

class ExtraRange : public Upgrade {
public:
    ExtraRange();
    ExtraRange(const ExtraRange& other);
    ~ExtraRange() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // EXTRA_RANGE_H