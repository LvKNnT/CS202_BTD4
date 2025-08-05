#ifndef TRIPLE_SHOT_H
#define TRIPLE_SHOT_H

#include "../../Upgrade.h"

class TripleShot : public Upgrade {
public:
    TripleShot();
    TripleShot(const TripleShot& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~TripleShot() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // TRIPLE_SHOT_H