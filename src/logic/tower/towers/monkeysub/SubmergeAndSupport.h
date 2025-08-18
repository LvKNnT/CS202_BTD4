#ifndef SUBMERGE_AND_SUPPORT_H
#define SUBMERGE_AND_SUPPORT_H

#include "../../Upgrade.h"

class SubmergeAndSupport : public Upgrade {
public:
    SubmergeAndSupport();
    SubmergeAndSupport(const SubmergeAndSupport& other);
    ~SubmergeAndSupport() override = default;

    std::unique_ptr<Upgrade> clone() const override;

    // Override all methods from Upgrade
    void loadTexture() override;
    void update(std::vector<std::unique_ptr<Attack>>& attacks, AttackBuff& attackBuff, std::unique_ptr<Skill>& skill, std::vector<std::unique_ptr<Skill>>& passiveSkills, MapManager& mapManager, ResourceManager& resourceManager) override;
    std::unique_ptr<Upgrade> buy() override;
};

#endif // SUBMERGE_AND_SUPPORT_H