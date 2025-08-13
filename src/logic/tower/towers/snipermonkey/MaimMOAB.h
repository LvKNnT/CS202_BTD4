#ifndef MAIM_MOAB_H
#define MAIM_MOAB_H

#include "../../Upgrade.h"  

class MaimMOAB : public Upgrade {
public:
    MaimMOAB();
    MaimMOAB(const MaimMOAB& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~MaimMOAB() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // MAIM_MOAB_H