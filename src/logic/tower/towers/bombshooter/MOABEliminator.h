#ifndef MOAB_ELIMINATOR_H
#define MOAB_ELIMINATOR_H

#include "../../Upgrade.h"

class MOABEliminator : public Upgrade {
public:
    MOABEliminator();
    MOABEliminator(const MOABEliminator& other);
    ~MOABEliminator() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // MOAB_ELIMINATOR_H