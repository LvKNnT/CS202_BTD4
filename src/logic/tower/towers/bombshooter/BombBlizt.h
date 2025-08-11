#ifndef BOMB_BLIZT_H
#define BOMB_BLIZT_H

#include "../../Upgrade.h"

class BombBlizt : public Upgrade {
public: 
    BombBlizt();
    BombBlizt(const BombBlizt& other);
    ~BombBlizt() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::unique_ptr<Skill>& passiveSkill, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // BOMB_BLIZT_H