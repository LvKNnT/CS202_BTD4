#ifndef DIFFICULTYUNITS_H
#define DIFFICULTYUNITS_H

#include "../LogicInfo.h"

#include <map>

enum class Difficulty {
    Easy,   // Easy difficulty
    Medium, // Medium difficulty
    Hard,   // Hard difficulty
    Impoppable  // Impoppable difficulty
};

// Singleton
class DifficultyInfo {
private:    
    std::map<Difficulty, LogicInfo> info;
    
    DifficultyInfo();
    DifficultyInfo(const DifficultyInfo&) = delete;
    DifficultyInfo& operator= (const DifficultyInfo&) = delete;

public:
    static DifficultyInfo& Instance();
    LogicInfo getDifficultyInfo(Difficulty difficulty);
};

#endif // DIFFICULTYUNITS_H