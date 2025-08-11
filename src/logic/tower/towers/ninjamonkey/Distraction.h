#ifndef DISTRACTION_H
#define DISTRACTION_H

#include "../../Upgrade.h"

class Distraction : public Upgrade {
public:
    Distraction();
    Distraction(const Distraction& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~Distraction() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // DISTRACTION_H