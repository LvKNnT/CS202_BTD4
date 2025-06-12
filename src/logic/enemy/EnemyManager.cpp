#include "EnemyManager.h"
#include <iostream>
#include <filesystem>

EnemyManager::EnemyManager(const EnemyManager& other) {
    for(const std::unique_ptr<Enemy>& enemy : other.enemyList) {
        // Clone each enemy and add it to the new manager
        enemyList.push_back(enemy->clone());
    }
}

EnemyManager& EnemyManager::operator=(const EnemyManager& other) {
    if (this != &other) {
        enemyList.clear(); // Clear current list
        for(const std::unique_ptr<Enemy>& enemy : other.enemyList) {
            // Clone each enemy and add it to the new manager
            enemyList.push_back(enemy->clone());
        }
    }
    return *this;
}

std::unique_ptr<Enemy> EnemyManager::createEnemy(BloonType type, Vector2 position) {
    // Factory method to create enemies based on type
    switch (type) {
        case BloonType::Red:
            return std::make_unique<Red>(position);
        default:
            return nullptr; // Return nullptr if type is not recognized
    }
}

void EnemyManager::spawnEnemy(BloonType type, Vector2 position) {
    // Create a new enemy using the factory method and add it to the list
    std::unique_ptr<Enemy> enemy = createEnemy(type, position);
    
    enemyList.push_back(std::move(enemy));
}

void EnemyManager::drawEnemies(const Map& map) const {
    // Logic to draw all active enemies
    for (const auto& enemy : enemyList) {
        if (enemy->isActive()) {
            if(map.getPointType(enemy->getTrackIndex()) == Point::Type::Enemy) {
                // Draw the enemy only if it is on the enemy path
                enemy->draw();
            }
        }
    }
}

void EnemyManager::updateEnemies(const Map& map) {
    for (auto it = enemyList.begin(); it != enemyList.end(); ) {
        if ((*it)->isActive()) {
            int result = run(**it, map);

            if (result == -1) {
                // Enemy reached the end — remove and destroy it
                it = enemyList.erase(it);  // erase returns the next iterator
                continue;  // Skip the increment, already moved to next
            }
        }
        ++it;
    }
}

int EnemyManager::run(Enemy& enemy, const Map& map) {
    // Preparation
    float elaspedTime = GetFrameTime();
    Vector2 position = enemy.getPosition();
    int trackIndex = enemy.getTrackIndex();
    int speed = enemy.getSpeed();
    
    Vector2 nextPoint = map.getNextPoint(trackIndex);
    Vector2 direction = {nextPoint.x - position.x, nextPoint.y - position.y};
    float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

    // Continously move the enemy until it reaches the next point
    while(elaspedTime > 0.0f || map.isLastPoint(trackIndex)) {
        nextPoint = map.getNextPoint(trackIndex);
        direction = {nextPoint.x - position.x, nextPoint.y - position.y};
        distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
        
        // Move the enemy towards the next point
        if(speed * elaspedTime < distance) {
            position.x += direction.x / distance * speed * elaspedTime;
            position.y += direction.y / distance * speed * elaspedTime;
            elaspedTime = 0.0f; // Use all the rest of the time
        }
        else {
            position = nextPoint; // Move to the next point
            trackIndex++; // Move to the next point in the path
            elaspedTime -= distance / speed; // Reduce the elapsed time by the time taken to reach the next point
        }
        
        if (map.isLastPoint(trackIndex)) {
            // Before returning, update the enemy's position and track index
            enemy.setPosition(position);
            enemy.setTrackIndex(trackIndex); // Move to the next point in the path

            enemy.die(); // Call the die method to handle reaching the end of the path

            return -1; // Enemy has reached the end of the path
        }
    }

    // Before returning, update the enemy's position and track index
    enemy.setPosition(position);
    enemy.setTrackIndex(trackIndex); // Move to the next point in the path

    // If the enemy has not reached the end of the path, return 0
    return 0;
}

void EnemyManager::updateActiveEnemies(Enemy& enemy, const Map& map) {
    // Update the enemy's position and state based on the map
    int result = run(enemy, map);
    
    if (result == -1) {
        // Handle enemy reaching the end of the path
        // You can implement logic to remove the enemy or handle lives lost
        std::cout << "Enemy reached the end of the path!" << std::endl;
    }
}

