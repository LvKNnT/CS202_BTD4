#ifndef REALLY_BIG_BOMBS_H
#define REALLY_BIG_BOMBS_H

#include "../../Upgrade.h"

class ReallyBigBombs : public Upgrade {
public:
    ReallyBigBombs();
    ReallyBigBombs(const ReallyBigBombs& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~ReallyBigBombs() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // REALLY_BIG_BOMBS_H