#include "RoundManager.h"

const Round& RoundManager::getRegularRound(int roundNumber) const {
    // Get the round from the regular round spawner
    return regularRoundSpawner.getRound(roundNumber);
}

const Round& RoundManager::getAlternativeRound(int roundNumber) const {
    // Get the round from the alternative round spawner
    return alternativeRoundSpawner.getRound(roundNumber); // Assuming you want to use the same spawner for both
}

const Round& RoundManager::getReverseRound(int roundNumber) const {
    // Get the round from the reverse round spawner
    return reverseRoundSpawner.getRound(roundNumber);
}