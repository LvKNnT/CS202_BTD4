#ifndef BLOON_CRUSH_H
#define BLOON_CRUSH_H

#include "../../Upgrade.h"

class BloonCrush : public Upgrade {
public:
    BloonCrush();
    BloonCrush(const BloonCrush& other);
    ~BloonCrush() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // BLOON_CRUSH_H