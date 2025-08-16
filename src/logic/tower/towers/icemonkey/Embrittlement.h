#ifndef EMBRITTLEMENT_H
#define EMBRITTLEMENT_H

#include "../../Upgrade.h"

class Embrittlement : public Upgrade {
public:
    Embrittlement();
    Embrittlement(const Embrittlement& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~Embrittlement() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // EMBRITTLEMENT_H