#include "ReverseMode.h"
#include <iostream>
#include <cmath>

std::unique_ptr<Mode> ReverseModePlayer::clone() const {
    return std::make_unique<ReverseModePlayer>(*this);
}

void ReverseModePlayer::playRound(const RoundManager& roundManager, int roundNumber) {
    if(currentRoundNumber != roundNumber) {
        currentRound = roundManager.getReverseRound(roundNumber);
        timer = 0.0f;
        currentRoundNumber = roundNumber;
    }
}

std::vector<std::pair<BloonType, BloonProperties>> ReverseModePlayer::getEnemies(const RoundManager& roundManager) {
    std::vector<std::pair<BloonType, BloonProperties>> bloonList;

    // playing round
    timer += GetFrameTime();
    for(auto& [type, properties, count, startTime, endTime, bloonCount] : currentRound.bloonTypes) {
        if(bloonCount >= count) continue;

        // special case
        if(count == 1) {
            if(bloonCount > 0 || timer < startTime) continue;

            bloonCount = 1;
            bloonList.emplace_back(type, properties);

            continue;
        }

        float interval = (endTime - startTime) / (count - 1);
        for(float spawnTime = startTime + bloonCount * interval; spawnTime <= timer && bloonCount <= count; spawnTime += interval) {
            bloonList.emplace_back(type, properties);
            bloonCount++;
        }
    }

    return bloonList;
}

bool ReverseModePlayer::canPlayNextRound(bool isClear) const {
    if(!isClear) return false;

    for(const auto& wave : currentRound.bloonTypes) {
        if(wave.bloonCount < wave.count) {
            return false; // Not all bloons in the current round have been cleared
        }
    }
    return true; // All bloons in the current round have been cleared
}

int ReverseModePlayer::getRoundReward() {
    int reward = currentRound.extraCash;
    currentRound.extraCash = 0; 
    return reward;
}

bool ReverseModePlayer::setAutoPlay(bool autoPlay) {
    return autoPlay;
}