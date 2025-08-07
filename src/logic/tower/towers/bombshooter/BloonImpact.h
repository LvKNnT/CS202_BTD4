#ifndef BLOON_IMPACT_H
#define BLOON_IMPACT_H

#include "../../Upgrade.h"

class BloonImpact : public Upgrade {
public:
    BloonImpact();
    BloonImpact(const BloonImpact& other);
    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;

    std::unique_ptr<Upgrade> buy() override;
};

#endif // BLOON_IMPACT_H