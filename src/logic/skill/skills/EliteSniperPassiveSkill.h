#ifndef ELITE_SNIPER_PASSIVE_SKILL_H
#define ELITE_SNIPER_PASSIVE_SKILL_H

#include "../Skill.h"

class EliteSniperPassiveSkill : public Skill {
private:
    std::set<int> buffedTowerIds; // Store IDs of buffed towers

public:
    EliteSniperPassiveSkill();
    ~EliteSniperPassiveSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) override;
    void inActivateSkill() override;
};

#endif // ELITE_SNIPER_PASSIVE_SKILL_H