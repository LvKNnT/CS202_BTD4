#include "EnemyManager.h"
#include <iostream>
#include <filesystem>

EnemyManager::EnemyManager(EnemyModifies modifies)
    : currentModifies(modifies) { // Initialize with default EnemyModifies
    // Initialize unique_ptr
    enemySpawner = std::make_unique<EnemySpawner>();
}

EnemyManager::EnemyManager(const EnemyManager& other) {
    if (this != &other) {
        currentModifies = other.currentModifies; // Copy the current modifies
        enemySpawner = other.enemySpawner->clone();

        enemyList.clear();
        for(const std::unique_ptr<Enemy>& enemy : other.enemyList) {
            enemyList.push_back(enemy->clone());
        }
    }
    else {
        // should not be here
        std::cerr << "Error: Attempted to copy EnemyManager to itself." << std::endl;
    }
}

EnemyManager& EnemyManager::operator=(const EnemyManager& other) {
    if (this != &other) {
        currentModifies = other.currentModifies; 
        enemySpawner = other.enemySpawner->clone(); 

        enemyList.clear(); 
        for(const std::unique_ptr<Enemy>& enemy : other.enemyList) {
            enemyList.push_back(enemy->clone());
        }
    }
    else {
        // should not be here
        std::cerr << "Error: Attempted to assign EnemyManager to itself." << std::endl;
    }
    return *this;
}

void EnemyManager::spawnEnemy(BloonType type, BloonProperties properties, Vector2 position, int pathIndex) {
    std::unique_ptr<Enemy> enemy = enemySpawner->getEnemy(type, properties, position, pathIndex, currentModifies);
    
    if (enemy) {
        enemyList.push_back(std::move(enemy));
    } else {
        std::cerr << "Failed to spawn enemy of type: " << static_cast<int>(type) << std::endl;
    }
}

std::vector<std::unique_ptr<Enemy>> EnemyManager::spawnChildrenEnemies(Enemy* enemy) {
    std::vector<std::unique_ptr<Enemy>> childrenEnemies = enemySpawner->getChildrenEnemies(enemy, currentModifies);
    
    return childrenEnemies; // Return the spawned children enemies
}

void EnemyManager::drawEnemies() const {
    for (const auto& enemy : enemyList) {
        if(enemy) {
            enemy->draw();
        } else {
            std::cerr << "Enemy is null!" << std::endl;
        }
    }
}

void EnemyManager::updateEnemies() {
    for(auto it = enemyList.begin(); it != enemyList.end(); ++it) {
        enemySpawner->getRegrowEnemy(*it, currentModifies); 
    }
}

void EnemyManager::unLoad() {
    for (auto& enemy : enemyList) {
        if (enemy) {
            enemy->unLoad(); // Unload the enemy resources
        } else {
            std::cerr << "Enemy is null during unload!" << std::endl;
        }
    }
    enemyList.clear(); // Clear the list of enemies
}