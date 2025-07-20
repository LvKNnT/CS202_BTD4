#ifndef TOWER_INFO_H
#define TOWER_INFO_H

#include <string>

// Provide basic information about towers for UI/UX
class TowerInfo {
public:
    std::string name;
    std::string description;
    int cost;
    int popCount;
    int sellPrice;
    
    std::string tagetPriority;

    std::string descriptionTop;
    std::string descriptionMiddle;
    std::string descriptionBottom;
    
    int upgradeCostTop;
    std::string upgradeDescriptionTop;
    int upgradeCostMiddle;
    std::string upgradeDescriptionMiddle;
    int upgradeCostBottom;
    std::string upgradeDescriptionBottom;

};
#endif // TOWER_INFO_H