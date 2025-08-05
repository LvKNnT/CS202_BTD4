#include "ApopalypseMode.h"
#include <iostream>
#include <cmath> 

std::unique_ptr<Mode> ApopalypseModePlayer::clone() const {
    return std::make_unique<ApopalypseModePlayer>(*this);
}

void ApopalypseModePlayer::playRound(const RoundManager& roundManager, int roundNumber) {
    if(currentRoundNumber != roundNumber) {
        currentRound = roundManager.getRegularRound(roundNumber);
        timer = 0.0f;
        currentRoundNumber = roundNumber;
    }
}

std::vector<std::pair<BloonType, BloonProperties>> ApopalypseModePlayer::getEnemies(const RoundManager& roundManager) {
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

bool ApopalypseModePlayer::canPlayNextRound(bool isClear) const {
    for(const auto& wave : currentRound.bloonTypes) {
        if(wave.bloonCount < wave.count) {
            return false; // Not all bloons in the current round have been cleared
        }
    }
    return true; // All bloons in the current round have been cleared
}

int ApopalypseModePlayer::getRoundReward() {
    int reward = currentRound.extraCash;
    currentRound.extraCash = 0; 
    return reward;
}

bool ApopalypseModePlayer::setAutoPlay(bool autoPlay) {
    return true;
}