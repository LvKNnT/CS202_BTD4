#ifndef BLOON_SABOTAGE_SKILL_H
#define BLOON_SABOTAGE_SKILL_H

#include "../Skill.h"

#include <unordered_map>

class BloonSabotageSkill : public Skill {
private:
    float duration;
    bool isSkillActivating;
    std::shared_ptr<Tower> closestTower;
    //std::unordered_map<int, bool> affectedEnemies;

public:
    BloonSabotageSkill();
    ~BloonSabotageSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) override;
    void inActivateSkill() override;
};

#endif // BLOON_SABOTAGE_SKILL_H