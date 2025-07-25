#include "ModeManager.h"
#include <iostream>
#include <fstream>

void ModeManager::setMode(ModeType modeType) {
    // Use the modeSpawner to get the mode based on the type
    currentMode = modeSpawner.getMode(modeType).clone();
    currentModeType = modeType;
    
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

void ModeManager::save(const std::string& filePath) const {
    if (!currentMode) {
        std::cerr << "save: No current mode set\n";
        return;
    }

    std::fstream file(filePath, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for saving mode." << std::endl;
        return;
    }

    // file << "mode\n";
    file << static_cast<int>(currentModeType) << std::endl;
    file.close();
}

void ModeManager::load(const std::string& filePath) {
    std::fstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for loading mode." << std::endl;
        return;
    } 

    // skip 2 lines
    std::string line;
    std::getline(file, line); 
    std::getline(file, line); 
    
    int modeTypeInt;
    file >> modeTypeInt; 
    ModeType modeType = static_cast<ModeType>(modeTypeInt);
    
    setMode(modeType);
    
    std::cerr << "Loaded mode type: " << modeTypeInt << std::endl;
    
    file.close();
}