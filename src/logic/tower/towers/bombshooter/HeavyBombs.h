#ifndef HEAVY_BOMBS_H
#define HEAVY_BOMBS_H

#include "../../Upgrade.h"

class HeavyBombs : public Upgrade {
public:
    HeavyBombs();
    HeavyBombs(const HeavyBombs& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~HeavyBombs() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // HEAVY_BOMBS_H