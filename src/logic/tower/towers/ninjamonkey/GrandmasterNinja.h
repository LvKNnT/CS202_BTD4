#ifndef GRANDMASTER_NINJA_H
#define GRANDMASTER_NINJA_H

#include "../../Upgrade.h"

class GrandmasterNinja : public Upgrade {
public:
    GrandmasterNinja();
    GrandmasterNinja(const GrandmasterNinja& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~GrandmasterNinja() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // GRANDMASTER_NINJA_H