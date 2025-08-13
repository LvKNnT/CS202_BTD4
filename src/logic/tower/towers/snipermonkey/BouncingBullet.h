#ifndef BOUNCING_BULLET_H
#define BOUNCING_BULLET_H

#include "../../Upgrade.h"

class BouncingBullet : public Upgrade {
public:
    BouncingBullet();
    BouncingBullet(const BouncingBullet& other);
    ~BouncingBullet() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // BOUNCING_BULLET_H