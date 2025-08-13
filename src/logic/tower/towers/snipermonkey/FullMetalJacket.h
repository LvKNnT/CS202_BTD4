#ifndef FULL_META_JACKET_H
#define FULL_META_JACKET_H

#include "../../Upgrade.h"

class FullMetalJacket : public Upgrade {
public:
    FullMetalJacket();
    FullMetalJacket(const FullMetalJacket& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~FullMetalJacket() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;

};

#endif // FULL_META_JACKET_H