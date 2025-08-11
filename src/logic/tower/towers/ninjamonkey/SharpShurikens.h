#ifndef SHARP_SHURIKENS_H
#define SHARP_SHURIKENS_H

#include "../../Upgrade.h"

class SharpShurikens : public Upgrade {
public:
    SharpShurikens();
    SharpShurikens(const SharpShurikens& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~SharpShurikens() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // SHARP_SHURIKENS_H