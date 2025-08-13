#ifndef CLUSTER_BOMBS_H
#define CLUSTER_BOMBS_H

#include "../../Upgrade.h"

class ClusterBombs : public Upgrade {
public: 
    ClusterBombs();
    ClusterBombs(const ClusterBombs& other);
    ~ClusterBombs() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // CLUSTER_BOMBS_H