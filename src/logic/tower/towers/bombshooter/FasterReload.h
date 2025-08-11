#ifndef FASTER_RELOAD_H
#define FASTER_RELOAD_H

#include "../../Upgrade.h"

class FasterReload : public Upgrade {
public:
    FasterReload();
    FasterReload(const FasterReload& other);
    ~FasterReload() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // FASTER_RELOAD_H