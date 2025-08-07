#ifndef PLASMA_MONKEY_FAN_CLUB_SKILL_H
#define PLASMA_MONKEY_FAN_CLUB_SKILL_H

#include "../Skill.h"

class PlasmaMonkeyFanClubSkill : public Skill {
private:
    float duration; // Duration of the skill effect
    std::vector<std::weak_ptr<Tower>> closestTowers; // List of closest towers to activate

public:
    PlasmaMonkeyFanClubSkill();
    ~PlasmaMonkeyFanClubSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;
    
    void loadTexture() override;
    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager) override;
    void inActivateSkill() override;
};

#endif // PLASMA_MONKEY_FAN_CLUB_SKILL_H