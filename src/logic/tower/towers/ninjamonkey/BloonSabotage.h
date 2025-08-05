#ifndef BLOON_SABOTAGE_H
#define BLOON_SABOTAGE_H

#include "../../Upgrade.h"

class BloonSabotage : public Upgrade {
public:
    BloonSabotage();
    BloonSabotage(const BloonSabotage& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~BloonSabotage() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // BLOON_SABOTAGE_H