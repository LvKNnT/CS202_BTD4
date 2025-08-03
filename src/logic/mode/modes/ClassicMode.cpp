#include "ClassicMode.h"
#include <iostream>
#include <cmath> 

std::unique_ptr<Mode> ClassicModePlayer::clone() const {
    return std::make_unique<ClassicModePlayer>(*this);
}

void ClassicModePlayer::playRound(const RoundManager& roundManager, int roundNumber) {
    if(currentRoundNumber != roundNumber) {
        std::cerr << "Playing round: " << roundNumber << std::endl;
        currentRound = roundManager.getRegularRound(roundNumber);
        timer = 0.0f;
        currentRoundNumber = roundNumber;
    }
}

std::vector<std::pair<BloonType, BloonProperties>> ClassicModePlayer::getEnemies(const RoundManager& roundManager) {
    std::vector<std::pair<BloonType, BloonProperties>> bloonList;

    // playing round
    int counter = 0;
    timer += GetFrameTime();
    for(auto& [type, properties, count, startTime, endTime, bloonCount] : currentRound.bloonTypes) {
        if(bloonCount > count) continue;

        // special case
        if(count == 1) {
            if(bloonCount == 0 || timer < startTime) continue;

            bloonCount = 2;
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

bool ClassicModePlayer::canPlayNextRound(bool isClear) const {
    return timer >= currentRound.bloonTypes.back().endTime && isClear;
}

int ClassicModePlayer::getRoundReward() {
    int reward = currentRound.extraCash;
    currentRound.extraCash = 0; 
    return reward;
}

bool ClassicModePlayer::setAutoPlay(bool autoPlay) {
    return autoPlay;
}