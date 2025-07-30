#ifndef VERY_QUICK_SHOTS_H
#define VERY_QUICK_SHOTS_H

#include "../../Upgrade.h"

class VeryQuickShots : public Upgrade {
public:
    VeryQuickShots();
    VeryQuickShots(const VeryQuickShots& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~VeryQuickShots() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // VERY_QUICK_SHOTS_H