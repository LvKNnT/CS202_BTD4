#ifndef MOAB_MAULER_H
#define MOAB_MAULER_H

#include "../../Upgrade.h"

class MOABMauler : public Upgrade {
public:
    MOABMauler();
    MOABMauler(const MOABMauler& other);
    ~MOABMauler() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // MOAB_MAULER_H