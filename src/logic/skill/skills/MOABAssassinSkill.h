#ifndef MOAB_ASSASSIN_SKILL_H
#define MOAB_ASSASSIN_SKILL_H

#include "../Skill.h"

class MOABAssassinSkill : public Skill {
public:
    MOABAssassinSkill();
    ~MOABAssassinSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) override;
    void inActivateSkill() override;
};

#endif // MOAB_ASSASSIN_SKILL_H