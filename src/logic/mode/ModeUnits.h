#ifndef MODE_UNITS_H
#define MODE_UNITS_H

#include "../LogicInfo.h"

#include <map>

enum class ModeType {
    Classic,
    Alternative,
    Reverse,
    Apopalypse
};

// Singleton
class ModeInfo {
private:
    std::map<ModeType, LogicInfo> info;
    
    ModeInfo();
    ModeInfo(const ModeInfo&) = delete;
    ModeInfo& operator=(const ModeInfo&) = delete;

public:
    static ModeInfo& Instance();
    LogicInfo getModeInfo(ModeType modeType);
};

#endif // MODE_UNITS_H