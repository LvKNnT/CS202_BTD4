#ifndef GRAND_SABOTEUR_H
#define GRAND_SABOTEUR_H

#include "../../Upgrade.h"

class GrandSaboteur : public Upgrade {
public:
    GrandSaboteur();
    GrandSaboteur(const GrandSaboteur& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~GrandSaboteur() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // GRAND_SABOTEUR_H