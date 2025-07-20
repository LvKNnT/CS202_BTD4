#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {
    init();
}

ResourceManager::ResourceManager(Difficulty difficulty) : currentDifficulty(difficulty) {
    init();
}

ResourceManager::ResourceManager(const ResourceManager& other)
    : towerModifier(other.towerModifier), enemyModifier(other.enemyModifier), currentDifficulty(other.currentDifficulty),
      resourceTemplates(other.resourceTemplates) {
}

ResourceManager& ResourceManager::operator=(const ResourceManager& other) {
    if (this != &other) {
        towerModifier = other.towerModifier;
        enemyModifier = other.enemyModifier;
        currentDifficulty = other.currentDifficulty;
        resourceTemplates = other.resourceTemplates;
    } else {
        // should not be here
        std::cerr << "ResourceManager assignment operator called on self-assignment." << std::endl;
    }
    return *this;
}

void ResourceManager::init() {
    // Initialize the tower and enemy modifiers
    towerModifier.init();
    enemyModifier.init();

    // Initialize the resource templates based on the current difficulty
    resourceTemplates[Difficulty::Easy] = Resource(650, 200, 1, 40);
    resourceTemplates[Difficulty::Medium] = Resource(650, 150, 1, 60);
    resourceTemplates[Difficulty::Hard] = Resource(650, 100, 6, 80);
    resourceTemplates[Difficulty::Impoppable] = Resource(650, 1, 6, 100);
}

const Resource& ResourceManager::getResource(Difficulty type) const {
    // Find the resource for the given difficulty type
    auto it = resourceTemplates.find(type);
    if (it != resourceTemplates.end()) {
        return it->second;
    }
    
    // should not be here
    std::cerr << "Difficulty type not found: " << static_cast<int>(type) << std::endl;
    return resourceTemplates.at(Difficulty::Easy); // Return default resource if not found
}
const TowerModifies& ResourceManager::getTowerModifies() const {
    return towerModifier.getDifficultyUnits(currentDifficulty);
}
const EnemyModifies& ResourceManager::getEnemyModifies() const {
    return enemyModifier.getDifficultyUnits(currentDifficulty);
}