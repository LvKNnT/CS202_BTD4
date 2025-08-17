#include "DifficultyUnits.h"

DifficultyInfo::DifficultyInfo() {
    info[Difficulty::Easy]["name"] = "Easy";
    info[Difficulty::Easy]["description"] = "Start with 200 lives, $650 starting cash, win Rounds 1-40, all towers and upgrades cost 15% less than normal, all bloons move the slowest, at about -9% Medium speed, and the Round 40 MOAB has 66% HP.";
    
    info[Difficulty::Medium]["name"] = "Medium";
    info[Difficulty::Medium]["description"] = "Start with 150 lives, $650 starting cash, win Rounds 1-60, all towers and upgrades cost their normal prices, and all bloons move at standard speed (+10% faster than on Easy).";
    
    info[Difficulty::Hard]["name"] = "Hard";
    info[Difficulty::Hard]["description"] = "Start with 100 lives, $650 starting cash, win Rounds 3-80, all towers and upgrades cost +8% more, and all bloons move about +13% faster than on Medium (+25% faster than on Easy).";
    
    info[Difficulty::Impoppable]["name"] = "Impoppable";
    info[Difficulty::Impoppable]["description"] = "Start with 1 life only, $650 starting cash, win Rounds 6-100, all towers and upgrades cost +20% more, and all bloons move about +13% faster than on Medium (+25% faster than on Easy).";
}

DifficultyInfo& DifficultyInfo::Instance() {
    static DifficultyInfo instance;
    return instance;
}

LogicInfo DifficultyInfo::getDifficultyInfo(Difficulty difficulty) {
    return info[difficulty];
}
