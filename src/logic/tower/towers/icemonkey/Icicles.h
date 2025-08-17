#ifndef ICICLES_H
#define ICICLES_H

#include "../../Upgrade.h"

class Icicles : public Upgrade {
public:
    Icicles();
    Icicles(const Icicles& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~Icicles() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ICICLES_H