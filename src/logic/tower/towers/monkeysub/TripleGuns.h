#ifndef TRIPLE_GUNS_H
#define TRIPLE_GUNS_H

#include "../../Upgrade.h"

class TripleGuns : public Upgrade {
public:
    TripleGuns();
    TripleGuns(const TripleGuns& other);
    ~TripleGuns() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // TRIPLE_GUNS_H