#ifndef QUICK_SHOTS_H
#define QUICK_SHOTS_H

#include "../../Upgrade.h"

class QuickShots : public Upgrade {
public:
    QuickShots();
    QuickShots(const QuickShots& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~QuickShots() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // QUICK_SHOTS_H