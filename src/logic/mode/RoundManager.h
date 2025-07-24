#ifndef ROUND_MANAGER_H
#define ROUND_MANAGER_H

#include "rounds/RegularRoundSpawner.h"
#include "rounds/AlternativeRoundSpawner.h"
#include "rounds/ReverseRoundSpawner.h"

class RoundManager {
    friend class LogicManager; // Allow LogicManager to access private members

private:
    RegularRoundSpawner regularRoundSpawner; 
    AlternativeRoundSpawner alternativeRoundSpawner;
    ReverseRoundSpawner reverseRoundSpawner; 

public:
    RoundManager() = default;
    ~RoundManager() = default;

    const Round& getRegularRound(int roundNumber) const;
    const Round& getAlternativeRound(int roundNumber) const;
    const Round& getReverseRound(int roundNumber) const;
};

#endif // ROUND_MANAGER_H