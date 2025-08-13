#ifndef NIGHT_VISION_GOGGLES_H
#define NIGHT_VISION_GOGGLES_H

#include "../../Upgrade.h"

class NightVisionGoggles : public Upgrade {
public:
    NightVisionGoggles();
    NightVisionGoggles(const NightVisionGoggles& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~NightVisionGoggles() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // NIGHT_VISION_GOGGLES_H