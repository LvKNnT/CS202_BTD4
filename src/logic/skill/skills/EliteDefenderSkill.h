#ifndef ELITE_DEFENDER_SKILL_H
#define ELITE_DEFENDER_SKILL_H

#include "../Skill.h"

class EliteDefenderSkill : public Skill {
private:
    float duration;
    int currentHealth;
    std::weak_ptr<Tower> towerPtr; // Weak pointer to avoid circular reference

public:
    EliteDefenderSkill();
    ~EliteDefenderSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager, MapManager& mapManager) override;
    void inActivateSkill() override;
};

#endif // ELITE_DEFENDER_SKILL_H