#ifndef ULTRA_JUGGERNAUT_H
#define ULTRA_JUGGERNAUT_H

#include "../../Upgrade.h"

class UltraJuggernaut : public Upgrade {
public:
    UltraJuggernaut();
    UltraJuggernaut(const UltraJuggernaut& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~UltraJuggernaut() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ULTRA_JUGGERNAUT_H