#ifndef BOMB_BLIZT_SKILL_H
#define BOMB_BLIZT_SKILL_H

#include "../Skill.h"

class BombBliztSkill : public Skill {
private:
    int currentHealth;

public:
    BombBliztSkill();
    BombBliztSkill(ResourceManager& resourceManager);
    ~BombBliztSkill() override = default;

    // Clone method for polymorphism
    std::unique_ptr<Skill> clone() const override;

    void loadTexture() override;

    void update() override;
    bool canActivateSkill() const override;
    float getCooldown() const override;
    void activateSkill(std::shared_ptr<Tower> tower, std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Tower>>& towers, BulletManager& bulletManager, ResourceManager& resourceManager) override;
    void inActivateSkill() override;
};

#endif // BOMB_BLIZT_SKILL_H