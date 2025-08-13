#ifndef SUPPLY_DROP_H
#define SUPPLY_DROP_H

#include "../../Upgrade.h"

class SupplyDrop : public Upgrade {
public:
    SupplyDrop();
    SupplyDrop(const SupplyDrop& other);
    ~SupplyDrop() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SUPPLY_DROP_H