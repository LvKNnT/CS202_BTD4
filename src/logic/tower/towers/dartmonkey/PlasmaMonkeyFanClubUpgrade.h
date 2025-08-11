#ifndef PLASMA_MONKEY_FAN_CLUB_UPGRADE_H
#define PLASMA_MONKEY_FAN_CLUB_UPGRADE_H

#include "../../Upgrade.h"

class PlasmaMonkeyFanClubUpgrade : public Upgrade {
public:
    PlasmaMonkeyFanClubUpgrade();
    PlasmaMonkeyFanClubUpgrade(const PlasmaMonkeyFanClubUpgrade& other);
    
    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // PLASMA_MONKEY_FAN_CLUB_UPGRADE_H