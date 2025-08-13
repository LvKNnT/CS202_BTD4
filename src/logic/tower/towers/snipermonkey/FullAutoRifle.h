#ifndef FULL_ATO_RIFLE_H
#define FULL_ATO_RIFLE_H

#include "../../Upgrade.h"

class FullAutoRifle : public Upgrade {
public:
    FullAutoRifle();
    FullAutoRifle(const FullAutoRifle& other);
    ~FullAutoRifle() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // FULL_ATO_RIFLE_H