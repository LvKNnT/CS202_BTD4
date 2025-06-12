#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include "raylib.h"
#include "enemy/EnemyManager.h"
#include "map/Map.h"

class LogicManager {
public:
    LogicManager() = default;
    ~LogicManager() = default;

    // Initialize the game logic
    void Init();

    // Update the game logic
    void Update();

    // Draw the game logic elements
    void Draw() const;
private:
    EnemyManager enemyManager; // Manages all enemies in the game
    std::unique_ptr<Map> map; // The game map, which can be used for enemy paths and other logic // Should be MapManager

};

#endif // LOGICMANAGER_H