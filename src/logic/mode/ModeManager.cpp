#include "ModeManager.h"
#include <iostream>

void ModeManager::setMode(ModeType modeType) {
    // Use the modeSpawner to get the mode based on the type
    currentMode = modeSpawner.getMode(modeType).clone();
    
    // should not be here
    if (!currentMode) {
        std::cerr << "No mode found!\n";
    }
}

void ModeManager::playRound(int roundNumber) {
    if (currentMode) {
        currentMode->playRound(*roundManager, roundNumber);
        return;
    } 

    // should not be here
    std::cerr << "playRound: No current mode set\n";
}

std::vector<std::pair<BloonType, BloonProperties>> ModeManager::getEnemies() {
    if (currentMode) {
        return currentMode->getEnemies(*roundManager);
    }

    // should not be here
    std::cerr << "getEnemies: No current mode set\n";
    return {};
}

int ModeManager::getRoundReward() {
    if (currentMode) {
        return currentMode->getRoundReward();
    }

    // should not be here
    std::cerr << "getRoundReward: No current mode set\n";
    return 0;
}

bool ModeManager::setAutoPlay(bool autoPlay) {
    if (currentMode) {
        return currentMode->setAutoPlay(autoPlay);
    } 

    // should not be here
    std::cerr << "setAutoPlay: No current mode set\n";
    return false;
}

bool ModeManager::canPlayNextRound(bool isClear) const {
    if (currentMode) {
        return currentMode->canPlayNextRound(isClear);
    } 

    // should not be here
    std::cerr << "canPlayNextRound: No current mode set\n";
    return false;
}