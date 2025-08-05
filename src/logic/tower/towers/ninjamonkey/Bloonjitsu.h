#ifndef BLOONJITSU_H
#define BLOONJITSU_H

#include "../../Upgrade.h"

class Bloonjitsu : public Upgrade {
public:
    Bloonjitsu();
    Bloonjitsu(const Bloonjitsu& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~Bloonjitsu() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // BLOONJITSU_H