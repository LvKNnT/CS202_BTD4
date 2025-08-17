#include "ResourceManager.h"
#include <iostream>
#include <fstream>

void ResourceManager::initResource(Difficulty difficulty) {
    currentDifficulty = difficulty;
    currentResource = resourceSpawner.getResource(difficulty);
}

Resource& ResourceManager::getResource() {
    return currentResource;
}
const TowerModifies& ResourceManager::getTowerModifies() const {
    return towerModifier.getDifficultyUnits(currentDifficulty);
}
const EnemyModifies& ResourceManager::getEnemyModifies() const {
    return enemyModifier.getDifficultyUnits(currentDifficulty);
}

int ResourceManager::isEndGame() const {
    // Check if the game has ended based on the current resources
    if (currentResource.lives <= 0) {
        return -1; // Lose game
    }
    if (currentResource.currentRound > currentResource.maxRound) {
        return 1; // Win game
    }
    
    // If the game is still ongoing, return 0
    return 0; 
}

LogicInfo ResourceManager::getInfo() const {
    return currentResource.getInfo();
}

Difficulty ResourceManager::getDifficulty() const {
    return currentDifficulty;
}

void ResourceManager::save(const std::string& filePath, bool isRoundEnd) const {
    std::fstream file(filePath, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for saving resources." << std::endl;
        return;
    }

    // file << "resource\n";
    file << static_cast<int>(currentDifficulty) << " ";
    file << currentResource.cash << " ";
    file << currentResource.lives << " ";
    file << currentResource.currentRound + isRoundEnd << "\n";
    file.close();
}

void ResourceManager::load(const std::string& filePath) {
    std::fstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for loading resources." << std::endl;
        return;
    } 
    
    // skip 1 line
    std::string line;
    std::getline(file, line);

    int difficultyInt;
    file >> difficultyInt; 
    currentDifficulty = static_cast<Difficulty>(difficultyInt);
    initResource(currentDifficulty);

    file >> currentResource.cash;
    file >> currentResource.lives;
    file >> currentResource.currentRound;

    std::cerr << "Loaded resources: "
              << "Difficulty: " << static_cast<int>(currentDifficulty) << ", "
              << "Cash: " << currentResource.cash << ", "
              << "Lives: " << currentResource.lives << ", "
              << "Current Round: " << currentResource.currentRound << std::endl;

    file.close();
}