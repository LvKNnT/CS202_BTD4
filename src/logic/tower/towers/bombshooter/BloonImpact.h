#ifndef BLOON_IMPACT_H
#define BLOON_IMPACT_H

#include "../../Upgrade.h"

class BloonImpact : public Upgrade {
public:
    BloonImpact();
    BloonImpact(const BloonImpact& other);
    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;

    std::unique_ptr<Upgrade> buy() override;
};

#endif // BLOON_IMPACT_H