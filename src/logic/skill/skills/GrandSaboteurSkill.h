#ifndef GRAND_SABOTEUR_SKILL_H
#define GRAND_SABOTEUR_SKILL_H

#include "../Skill.h"

#include <unordered_map>
#include <map>
class GrandSaboteurSkill : public Skill {
private:
    float duration;
    bool isSkillActivating;
    std::unordered_map<int, bool> affectedEnemies;
    std::map<int, std::shared_ptr<Tower>> affectedTowers;
public:
    GrandSaboteurSkill();
    ~GrandSaboteurSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) override;
    void inActivateSkill() override;
};

#endif // GRAND_SABOTEUR_SKILL_H