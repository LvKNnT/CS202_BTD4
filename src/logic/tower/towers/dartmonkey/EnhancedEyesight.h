#ifndef ENHANCED_EYESIGHT_H
#define ENHANCED_EYESIGHT_H

#include "../../Upgrade.h"

class EnhancedEyesight : public Upgrade {
public:
    EnhancedEyesight();
    EnhancedEyesight(const EnhancedEyesight& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~EnhancedEyesight() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // ENHANCED_EYESIGHT_H