#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include "enemy/EnemyManager.h"
#include "map/MapManager.h"
#include "bullet/BulletManager.h"
#include "tower/TowerManager.h"

// This class handles the iteration between different game Logic managers
class LogicManager {
public:
    LogicManager() = default;
    ~LogicManager() = default;

    // Update methods for different game objects
    void updateEnemies(EnemyManager& enemyManager, MapManager& mapManager);
    void updateBullets(BulletManager& bulletManager, MapManager& mapManager);
    void updateTowers(TowerManager& towerManager, EnemyManager& enemyManager, BulletManager& bulletManager);

    // Update methods for interactions between game objects
    void updateBulletsHitEnemies(BulletManager& bulletManager, EnemyManager& enemyManager, MapManager& mapManager);
private:
    // Move should be used the same logic for all enemies
    /**
     * @return -1 if the enemy has reached the end of the path, otherwise returns 0
     */
    int runEnemy(Enemy& enemy, const Map& map);
    int runBullet(Bullet& bullet, const Map& map);
    bool checkCollision(const Bullet& bullet, const Enemy& enemy) const;
    std::vector<std::unique_ptr<Enemy>> getChildrenEnemies(EnemyManager& enemyManager, Enemy& enemy, int damage);

    // Support methods
    float Vector2Distance(Vector2& a, Vector2& b) const;
};

#endif // LOGICMANAGER_H