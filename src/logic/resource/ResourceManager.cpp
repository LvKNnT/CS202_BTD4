#include "ResourceManager.h"
#include <iostream>

void ResourceManager::initResource(Difficulty difficulty) {
    currentDifficulty = difficulty;
    currentResource = resourceSpawner.getResource(difficulty);
}

const Resource& ResourceManager::getResource(Difficulty difficulty) const {
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