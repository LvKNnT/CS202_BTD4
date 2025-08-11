#ifndef CALTROPS_H
#define CALTROPS_H

#include "../../Upgrade.h"

class Caltrops : public Upgrade {
public:
    Caltrops();
    Caltrops(const Caltrops& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~Caltrops() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // CALTROPS_H