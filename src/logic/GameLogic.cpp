#include "GameLogic.h"
#include <fstream>

void GameLogic::init() {
    // testing, should be jajaja whenever enter a new game
    std::cerr << "init jajaja" << std::endl;

    // Currently working on create new game 
    // parameters
    const Difficulty difficulty = Difficulty::Easy; // Default difficulty for testing
    const MapType mapType = MapType::MonkeyLane; // Default map type for testing

    resourceManager = ResourceManager(difficulty); // Initialize resource manager with difficulty

    // Re-initialize all the managers
    mapManager = MapManager();
    bulletManager = BulletManager();
    enemyManager = EnemyManager(resourceManager.getEnemyModifies());
    towerManager = TowerManager(resourceManager.getTowerModifies());

    // Optionally, spawn some initial enemies for testing
    mapManager.loadMap(mapType); // Load the Monkey Lane map
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
    // towerManager.spawnTower(TowerType::DartMonkey, {200.0f, 200.0f});
    // if(logicManager.isPutTower(towerManager, mapManager, TowerType::DartMonkey, {200.0f, 200.0f})) {
        towerManager.spawnTower(TowerType::DartMonkey, {200.0f, 200.0f});
    // }


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
    logicManager.updateBulletsHitEnemies(bulletManager, enemyManager, towerManager, mapManager);
    logicManager.updateEnemies(enemyManager, mapManager);
    logicManager.updateBullets(bulletManager, mapManager);
    logicManager.updateTowers(towerManager, enemyManager, bulletManager);
}

void GameLogic::draw() const {
    // Draw by the managers
    mapManager.drawMap();
    enemyManager.drawEnemies();
    towerManager.drawTowers();
    bulletManager.drawBullets();
}

void GameLogic::unLoad() {
    // Unload all game logic resources
    mapManager.unLoad();
    enemyManager.unLoad();
    bulletManager.unLoad();
    towerManager.unLoad();
}

bool GameLogic::isPutTower(TowerType type, Vector2 position) const {
    // Check if the tower can be placed at the given position
    return logicManager.isPutTower(towerManager, mapManager, type, position);
}