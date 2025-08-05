#ifndef DOUBLESHOT_H
#define DOUBLESHOT_H

#include "../../Upgrade.h"

class DoubleShot : public Upgrade {
public:
    DoubleShot();
    DoubleShot(const DoubleShot& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~DoubleShot() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // DOUBLESHOT_H