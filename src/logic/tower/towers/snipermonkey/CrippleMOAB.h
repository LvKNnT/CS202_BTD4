#ifndef CRIPLE_MOAB_H
#define CRIPLE_MOAB_H

#include "../../Upgrade.h"

class CrippleMOAB : public Upgrade {
public:
    CrippleMOAB();
    CrippleMOAB(const CrippleMOAB& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~CrippleMOAB() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // CRIPLE_MOAB_H