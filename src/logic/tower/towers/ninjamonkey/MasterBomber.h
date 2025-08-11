#ifndef MASTERBOMBER_H
#define MASTERBOMBER_H

#include "../../Upgrade.h"

class MasterBomber : public Upgrade {
public:
    MasterBomber();
    MasterBomber(const MasterBomber& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~MasterBomber() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // MASTERBOMBER_H