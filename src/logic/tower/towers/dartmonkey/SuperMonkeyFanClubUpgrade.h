#ifndef SUPER_MONKEY_FAN_CLUB_UPGRADE_H
#define SUPER_MONKEY_FAN_CLUB_UPGRADE_H

#include "../../Upgrade.h"

class SuperMonkeyFanClubUpgrade : public Upgrade {
public:
    SuperMonkeyFanClubUpgrade();
    SuperMonkeyFanClubUpgrade(const SuperMonkeyFanClubUpgrade& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~SuperMonkeyFanClubUpgrade() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SUPER_MONKEY_FAN_CLUB_UPGRADE_H