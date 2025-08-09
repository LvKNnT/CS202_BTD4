#ifndef SUPER_MONKEY_FAN_CLUB_SKILL_H
#define SUPER_MONKEY_FAN_CLUB_SKILL_H

#include "../Skill.h"

class SuperMonkeyFanClubSkill : public Skill {
private:
    float duration;
    std::vector<std::weak_ptr<Tower>> closestTowers;

public:
    SuperMonkeyFanClubSkill();
    ~SuperMonkeyFanClubSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) override;
    void inActivateSkill() override;
};

#endif // SUPER_MONKEY_FAN_CLUB_SKILL_H