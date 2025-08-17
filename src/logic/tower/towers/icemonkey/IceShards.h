#ifndef ICE_SHARDS_H
#define ICE_SHARDS_H

#include "../../Upgrade.h"

class IceShards : public Upgrade {
public:
    IceShards();
    IceShards(const IceShards& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~IceShards() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ICE_SHARDS_H