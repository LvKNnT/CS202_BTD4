#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "raylib.h"
#include <vector>
#include <memory>

// Include the necessary headers for enemy types
#include "Enemy.h"
#include "EnemySpawner.h"
#include "../level/EnemyModifies.h"

// This class manages all enemies in the game
class EnemyManager {
    friend class LogicManager; // Allow LogicManager to access private members

public:
    EnemyManager(EnemyModifies modifies = EnemyModifies());
    EnemyManager(const EnemyManager& other); 
    ~EnemyManager() = default;

    EnemyManager& operator=(const EnemyManager& other); 

    // Methods
    void spawnEnemy(BloonType type, BloonProperties properties, Vector2 position, int pathIndex = 0);
    std::vector<std::unique_ptr<Enemy> > spawnChildrenEnemies(Enemy* enemy, int round);
    void drawEnemies() const;
    void updateEnemies();

private:
    // Current enemy modifies
    // Note that enemyModifies is constant and should not be modified for each enemyManager instance.
    EnemyModifies currentModifies;
 
    // Instances
    std::unique_ptr<EnemySpawner> enemySpawner; // Factory to create enemies based on type

    // Collection to hold all active enemies
    std::vector<std::unique_ptr<Enemy> > enemyList;

    int currentEnemyId = 0;
};

#endif // ENEMYMANAGER_H