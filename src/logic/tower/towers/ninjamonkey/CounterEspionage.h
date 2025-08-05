#ifndef COUNTER_ESPINAGE_H
#define COUNTER_ESPINAGE_H

#include "../../Upgrade.h"

class CounterEspionage : public Upgrade {
public:
    CounterEspionage();
    CounterEspionage(const CounterEspionage& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~CounterEspionage() override = default;

    // Override all methods from Upgrade
    void loadTexture();

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<AttackPattern>& attackPattern, std::unique_ptr<Skill>& skill) override;
    std::unique_ptr<Upgrade> buy();
};

#endif // COUNTER_ESPINAGE_H