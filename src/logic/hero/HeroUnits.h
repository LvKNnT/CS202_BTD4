#ifndef HERO_UNITS_H
#define HERO_UNITS_H

#include "../LogicInfo.h"

#include <map>

enum class HeroType {
    Quincy,
    Benjamin,
    Rosalia,
    Etienne
};

// Singleton
class HeroInfo {
private:
    std::map<HeroType, LogicInfo> info;

    HeroInfo();
    HeroInfo(const HeroInfo&) = delete;
    HeroInfo& operator=(const HeroInfo&) = delete;

public:
    static HeroInfo& Instance();
    LogicInfo getHeroInfo(HeroType heroType);
};

#endif // HERO_UNITS_H