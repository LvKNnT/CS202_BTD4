#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../../include/raylib.h"
#include "LogicManager.h"
#include "enemy/EnemyManager.h"
#include "map/MapManager.h"
#include "bullet/BulletManager.h"
#include "tower/TowerManager.h"
#include "resource/ResourceManager.h"

class GameLogic {
public:
    GameLogic() = default;
    ~GameLogic() = default;
    
    // Initialize the game logic
    void init(); // only for testing, should not be called in production
    void init(Difficulty difficulty); // For loading new game

    // Update the game logic
    void update();

    // Draw the game logic elements
    void draw() const;

    // Unload all game logic resources
    void unLoad();

    // Supplyment methos for Game
    bool isPutTower(TowerType type, Vector2 position) const;

    // Save/Load
    
private:
    // Heavy/important game logic
    LogicManager logicManager; // Manages the game logic, including enemies and other game elements
    EnemyManager enemyManager; // Manages all enemies in the game
    MapManager mapManager; // Manages the current map
    BulletManager bulletManager; // Manages all bullets in the game
    TowerManager towerManager; // Manages all towers in the game

    // Light/less important game logic
    ResourceManager resourceManager; // Manages resources like cash, lives, and rounds
};

#endif // GAME_LOGIC_H