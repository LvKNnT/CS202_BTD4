#ifndef FRAG_BOMBS_H
#define FRAG_BOMBS_H

#include "../../Upgrade.h"

class FragBombs : public Upgrade {
public:
    FragBombs();
    FragBombs(const FragBombs& other);
    ~FragBombs() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // FRAG_BOMBS_H