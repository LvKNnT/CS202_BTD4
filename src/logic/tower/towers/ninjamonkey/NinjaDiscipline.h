#ifndef NINJA_DISCIPLINE_H
#define NINJA_DISCIPLINE_H

#include "../../Upgrade.h"

class NinjaDiscipline : public Upgrade {
public:
    NinjaDiscipline();
    NinjaDiscipline(const NinjaDiscipline& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~NinjaDiscipline() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // NINJA_DISCIPLINE_H