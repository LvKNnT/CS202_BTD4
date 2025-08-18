#ifndef ROUND_INFO_H
#define ROUND_INFO_H

#include "../LogicInfo.h"

#include <map>

// Singleton
class RoundInfo {
private:
    std::map<int, LogicInfo> info;

    RoundInfo();
    RoundInfo(const RoundInfo&) = delete;
    RoundInfo& operator=(const RoundInfo&) = delete;
    
public:
    static RoundInfo& Instance();
    LogicInfo getRoundInfo(int roundNum);
};

#endif // ROUND_INFO_H