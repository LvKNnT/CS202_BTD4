#ifndef STICKYBOMB_H
#define STICKYBOMB_H

#include "../../Upgrade.h"

class StickyBomb : public Upgrade {
public:
    StickyBomb();
    StickyBomb(const StickyBomb& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~StickyBomb() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // STICKYBOMB_H