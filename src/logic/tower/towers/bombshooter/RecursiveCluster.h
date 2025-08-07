#ifndef RECURSIVE_CLUSTER_H
#define RECURSIVE_CLUSTER_H

#include "../../Upgrade.h"

class RecursiveCluster : public Upgrade {
public: 
    RecursiveCluster();
    RecursiveCluster(const RecursiveCluster& other);
    ~RecursiveCluster() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // RECURSIVE_CLUSTER_H