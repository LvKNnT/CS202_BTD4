#ifndef SHINOBI_TACTICS_H
#define SHINOBI_TACTICS_H

#include "../../Upgrade.h"

class ShinobiTactics : public Upgrade {
public:
    ShinobiTactics();
    ShinobiTactics(const ShinobiTactics& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~ShinobiTactics() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // SHINOBI_TACTICS_H