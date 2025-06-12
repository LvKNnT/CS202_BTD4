#include "LogicManager.h"

void LogicManager::Init() {
    // Initialize the enemy manager or any other game logic components
    enemyManager = EnemyManager();

    // Initialize the map with a specific type, e.g., Jungle or MonkeyLane
    map = std::make_unique<Map>(Map::Type::MonkeyLane);

    // Optionally, spawn some initial enemies for testing
    enemyManager.spawnEnemy(BloonType::Red, map->getCurrentPoint(0)); // Spawn a Red bloon at position (100, 100)
}

void LogicManager::Update() {
    // Update the enemy manager or any other game logic components
    enemyManager.updateEnemies(*map);
}

void LogicManager::Draw() const {
    // Draw the enemies and the map
    map->draw();
    enemyManager.drawEnemies(*map);
}