#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include "enemy/EnemyManager.h"
#include "map/MapManager.h"
#include "bullet/BulletManager.h"
#include "tower/TowerManager.h"
#include "resource/ResourceManager.h"
#include "mode/ModeManager.h"

// This class handles the iteration between different game Logic managers
class LogicManager {
public:
    LogicManager() = default;
    ~LogicManager() = default;
    
    // Core logic
    void updateEnemies(EnemyManager& enemyManager, MapManager& mapManager);
    void updateBullets(BulletManager& bulletManager, MapManager& mapManager);
    void updateTowers(TowerManager& towerManager, EnemyManager& enemyManager, BulletManager& bulletManager);
    
    // Suplly for GameLogic
    bool isPutTower(const ResourceManager& resourceManager, const TowerManager& towerManager, const MapManager& mapManager, TowerType type, Vector2 position) const; 
    bool spawnTower(ResourceManager& resourceManager, TowerManager& towerManager, const MapManager& mapManager, TowerType type, Vector2 position);
    bool isUpgradeTower(const ResourceManager& resourceManager, const TowerManager& towerManager, Vector2 position, UpgradeUnits upgradeUnits) const;
    bool upgradeTower(ResourceManager& resourceManager, TowerManager& towerManager, Vector2 position, UpgradeUnits upgradeUnits);

    void playRound(ResourceManager& resourceManager, ModeManager& modeManager, EnemyManager& enemyManager, MapManager& mapManager);
    void playNextRound(ResourceManager& resourceManager);
    void setAutoPlay(ModeManager& modeManager, bool autoPlay);

    // Update methods for interactions between game objects
    void updateBulletsHitEnemies(BulletManager& bulletManager, EnemyManager& enemyManager, TowerManager& towerManager, MapManager& mapManager);
private:
    // Move should be used the same logic for all enemies
    /**
     * @return -1 if the enemy has reached the end of the path, otherwise returns 0
     */
    int runEnemy(Enemy& enemy, const Map& map);
    int runBullet(Bullet& bullet, const Map& map);
    bool checkCollision(const Bullet& bullet, const Enemy& enemy) const;
    std::vector<std::unique_ptr<Enemy>> getChildrenEnemies(EnemyManager& enemyManager, Enemy& enemy, int damage, int& popCount);

    // sub-methods
    float distancePointLine(Vector2 point, Vector2 lineStart, Vector2 lineEnd) const;
    bool autoPlayRound = true;
};

#endif // LOGICMANAGER_H