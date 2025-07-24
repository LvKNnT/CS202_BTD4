#include "AlternativeMode.h"
#include <iostream>
#include <cmath>

std::unique_ptr<Mode> AlternativeMode::clone() const {
    return std::make_unique<AlternativeMode>(*this);
}

void AlternativeMode::playRound(const RoundManager& roundManager, int roundNumber) {
    if(currentRoundNumber != roundNumber) {
        std::cerr << "Playing round: " << roundNumber << std::endl;
        currentRound = roundManager.getAlternativeRound(roundNumber);
        timer = 0.0f;
        currentRoundNumber = roundNumber;
    }
}

std::vector<std::pair<BloonType, BloonProperties>> AlternativeMode::getEnemies(const RoundManager& roundManager) {
    std::vector<std::pair<BloonType, BloonProperties>> bloonList;

    // playing round
    int counter = 0;
    timer += GetFrameTime();
    for(auto& [type, properties, count, startTime, endTime] : currentRound.bloonTypes) {
        if(timer < startTime) continue;

        // No more enemies
        if(count == 0) {
            ++counter;
            continue;
        }

        // An edge case of this approach
        // Unlucky tho...
        if(count == 1) {
            if(timer > startTime) {
                bloonList.emplace_back(type, properties);
                count = 0;
            }
            continue;
        }

        float interval = (endTime - startTime) / (count - 1);
        int lastIndex = static_cast<int>(floor((timer - startTime) / interval));
        for(int i = 0; i <= lastIndex; ++i) {
            bloonList.emplace_back(type, properties);
            --count;
            startTime += interval; 
        }
    }

    return bloonList;
}

bool AlternativeMode::canPlayNextRound(bool isClear) const {
    return timer >= currentRound.bloonTypes.back().endTime && isClear;
}

int AlternativeMode::getRoundReward() {
    int reward = currentRound.extraCash;
    currentRound.extraCash = 0; 
    return reward;
}

bool AlternativeMode::setAutoPlay(bool autoPlay) {
    return autoPlay;
}