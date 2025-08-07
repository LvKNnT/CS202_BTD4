#ifndef MISSILE_LAUNCHER_H
#define MISSILE_LAUNCHER_H

#include "../../Upgrade.h"

class MissileLauncher : public Upgrade {
public:
    MissileLauncher();
    MissileLauncher(const MissileLauncher& other);
    ~MissileLauncher() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    void loadTexture() override;

    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    
    std::unique_ptr<Upgrade> buy() override;
};

#endif // MISSILE_LAUNCHER_H