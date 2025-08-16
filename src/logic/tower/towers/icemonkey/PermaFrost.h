#ifndef PERMA_FROST_H
#define PERMA_FROST_H

#include "../../Upgrade.h"

class PermaFrost : public Upgrade {
public:
    PermaFrost();
    PermaFrost(const PermaFrost& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~PermaFrost() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // PERMA_FROST_H