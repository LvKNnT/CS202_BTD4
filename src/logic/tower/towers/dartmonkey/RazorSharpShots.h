#ifndef RAZOR_SHARP_SHOTS_H
#define RAZOR_SHARP_SHOTS_H

#include "../../Upgrade.h"

class RazorSharpShots : public Upgrade {
public:
    RazorSharpShots();
    RazorSharpShots(const RazorSharpShots& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~RazorSharpShots() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // RAZOR_SHARP_SHOTS_H