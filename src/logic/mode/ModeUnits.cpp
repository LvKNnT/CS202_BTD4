#include "ModeUnits.h"

ModeInfo::ModeInfo() {
    info[ModeType::Classic]["name"] = "Standard";
    info[ModeType::Classic]["description"] = "Bloons come from the opposite side of the tracks, and the order of Bloon waves in each round are reversed.";

    info[ModeType::Alternative]["name"] = "Alternate Bloons";
    info[ModeType::Alternative]["description"] = "Bloons have an altered RBE, making it more tricky.";
    
    info[ModeType::Reverse]["name"] = "Reverse";
    info[ModeType::Reverse]["description"] = "Bloons come from the opposite side of the tracks, and the order of Bloon waves in each round are reversed.";

    info[ModeType::Apopalypse]["name"] = "Apopalypse";
    info[ModeType::Apopalypse]["description"] = "Bloon waves progress without stopping.";
}

ModeInfo& ModeInfo::Instance() {
    static ModeInfo instance;
    return instance;
}

LogicInfo ModeInfo::getModeInfo(ModeType modeType) {
    return info[modeType];
}