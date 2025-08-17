#ifndef MAPUNITS_H
#define MAPUNITS_H

#include "../LogicInfo.h"

#include <map>

// Maps types
enum class MapType{
    MonkeyLane,
    ReverseMonkeyLane,
    Jungle,
    ReverseJungle,
    RinkRevenge,
    ReverseRinkRevenge,
    DuneSea,
    ReverseDuneSea,
    AttackOnBloon,
    ReverseAttackOnBloon
};

// Singleton
class MapInfo {
private:
    std::map<MapType, LogicInfo> info;

    MapInfo();
    MapInfo(const MapInfo&) = delete;
    MapInfo& operator=(const MapInfo&) = delete;
    
public:
    static MapInfo& Instance();
    LogicInfo getMapInfo(MapType mapType);
};

#endif // MAPUNITS_H