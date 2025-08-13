#ifndef SPIKE_O_PULT_H
#define SPIKE_O_PULT_H

#include "../../Upgrade.h"

class SpikeOPult : public Upgrade {
public:
    SpikeOPult();
    SpikeOPult(const SpikeOPult& other);
    std::unique_ptr<Upgrade> clone() const override;
    ~SpikeOPult() override = default;

    // Override all methods from Upgrade
    void loadTexture() override;

    // Upgrade does not need to update attacks, but we need to implement it
    void update(std::vector<std::unique_ptr<Attack> >& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill> >& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SPIKE_O_PULT_H