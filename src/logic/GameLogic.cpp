#include "GameLogic.h"
#include <fstream>

void GameLogic::init() {
    // Re-initialize all the managers
    mapManager = MapManager();
    enemyManager = EnemyManager();
    bulletManager = BulletManager();
    towerManager = TowerManager();

    // Optionally, spawn some initial enemies for testing
    mapManager.loadMap(MapType::MonkeyLane); // Load the Monkey Lane map
    // enemyManager.spawnEnemy(BloonType::Moab, mapManager.getCurrentMap().getCurrentPoint(0));
    {
        // testing all enemies
        enemyManager.spawnEnemy(BloonType::Red, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Blue, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Green, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Yellow, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Pink, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Black, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::White, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Purple, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Lead, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Zebra, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Rainbow, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Ceramic, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Moab, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Bfb, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Zomg, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Ddt, mapManager.getCurrentMap().getCurrentPoint(0));
        enemyManager.spawnEnemy(BloonType::Bad, mapManager.getCurrentMap().getCurrentPoint(0));
    }
    // bulletManager.spawnBullet(BulletType::Dart, {100.0f, 100.0f}, {10.0f, 10.0f}, 0.0f, 170, 20, 2, 60.0f);
    towerManager.spawnTower(TowerType::DartMonkey, {200.0f, 200.0f});

    // Resetting log file
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::trunc);
    
    if (flog.is_open()) {
        flog << "Game Logic Initialized" << std::endl;
        flog.close();
    } else {
        std::cerr << "Error: Failed to open log file for writing." << std::endl;
    }
}

void GameLogic::update() {
    // Update by the managers
    mapManager.updateMap();
    logicManager.updateBulletsHitEnemies(bulletManager, enemyManager, mapManager);
    logicManager.updateEnemies(enemyManager, mapManager);
    logicManager.updateBullets(bulletManager, mapManager);
    logicManager.updateTowers(towerManager, enemyManager, bulletManager);
}

void GameLogic::draw() const {
    // Draw by the managers
    mapManager.drawMap();
    enemyManager.drawEnemies();
    bulletManager.drawBullets();
    towerManager.drawTowers();
}

void GameLogic::unLoad() {
    // Unload all game logic resources
    mapManager.unLoad();
    enemyManager.unLoad();
    bulletManager.unLoad();
    towerManager.unLoad();
}