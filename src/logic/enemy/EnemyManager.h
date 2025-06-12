#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "raylib.h"
#include <vector>
#include <memory>

// Include the necessary headers for enemy types
#include "Enemy.h"
#include "Red.h"
#include "../map/Map.h"

class EnemyManager {
public:
    EnemyManager() = default;
    EnemyManager(const EnemyManager& other); 
    ~EnemyManager() = default;

    EnemyManager& operator=(const EnemyManager& other); 

    // Method to spawn enemies
    void spawnEnemy(BloonType type, Vector2 position);

    // Method to draw enemies
    void drawEnemies(const Map& map) const;

    // Method to update all enemies
    void updateEnemies(const Map& map);

private:
    // Collection to hold all active enemies
    std::vector<std::unique_ptr<Enemy> > enemyList; 
    std::unique_ptr<Enemy> createEnemy(BloonType type, Vector2 position);

    // Function 
    // Move should be used the same logic for all enemies
    /**
     * @return -1 if the enemy has reached the end of the path, otherwise returns 0
     */
    int run(Enemy& enemy, const Map& map);
    void updateActiveEnemies(Enemy& enemy, const Map& map); // Update the visibility of enemy
};

#endif // ENEMYMANAGER_H