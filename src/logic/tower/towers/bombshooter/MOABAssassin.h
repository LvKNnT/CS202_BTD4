#ifndef MOAB_ASSASSIN_H
#define MOAB_ASSASSIN_H

#include "../../Upgrade.h"

class MOABAssassin : public Upgrade {
public:
    MOABAssassin();
    MOABAssassin(const MOABAssassin& other);
    ~MOABAssassin() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // MOAB_ASSASSIN_H