#ifndef CROSS_BOW_H
#define CROSS_BOW_H

#include "../../Upgrade.h"

class CrossBow : public Upgrade {
public:
    CrossBow();
    CrossBow(const CrossBow& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~CrossBow() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // CROSS_BOW_H