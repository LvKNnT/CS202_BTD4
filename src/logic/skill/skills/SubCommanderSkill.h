#ifndef SUB_COMMANDER_SKILL_H
#define SUB_COMMANDER_SKILL_H

#include "../Skill.h"

class SubCommanderSkill : public Skill {
private:
    std::set<int> affectedTowers; // Store affected towers to avoid repeated buffs

public:
    SubCommanderSkill();
    ~SubCommanderSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) override;
    void inActivateSkill() override;
};

#endif // SUB_COMMANDER_SKILL_H