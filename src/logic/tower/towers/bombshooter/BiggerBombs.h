#ifndef BIGGER_BOMBS_H
#define BIGGER_BOMBS_H

#include "../../Upgrade.h"

class BiggerBombs : public Upgrade {
public:
    BiggerBombs();
    BiggerBombs(const BiggerBombs& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~BiggerBombs() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // BIGGER_BOMBS_H