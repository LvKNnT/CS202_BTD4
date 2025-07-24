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