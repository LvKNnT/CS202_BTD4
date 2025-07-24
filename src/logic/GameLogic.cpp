#include "GameLogic.h"
#include <fstream>

void GameLogic::init() {
    // testing, should be jajaja whenever enter a new game
    std::cerr << "init jajaja" << std::endl;

    // Currently working on create new game 
    // parameters
    const Difficulty difficulty = Difficulty::Easy; // Default difficulty for testing
    const MapType mapType = MapType::MonkeyLane; // Default map type for testing
    const ModeType modeType = ModeType::Alternative; // Default mode type for testing

    // stimulate what will happen in the game
    init(difficulty, mapType, modeType);

    spawnTower(TowerType::DartMonkey, {200.0f, 225.0f});
    std::cerr << resourceManager.getResource(difficulty).cash << std::endl;
    
    // Resetting log file
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::trunc);  
    
    if (flog.is_open()) {
        flog << "Game Logic Initialized" << std::endl;
        flog.close();
    } else {
        std::cerr << "Error: Failed to open log file for writing." << std::endl;
    }
}

void GameLogic::init(Difficulty difficulty, MapType mapType, ModeType modeType) {
    resourceManager.initResource(difficulty);
    mapManager.loadMap(mapType); 
    modeManager.setMode(modeType); 
    
    enemyManager = EnemyManager(resourceManager.getEnemyModifies());
    towerManager = TowerManager(resourceManager.getTowerModifies());
}

void GameLogic::update() {
    // Update game result
    if(resourceManager.isEndGame() != 0) {
        std::cerr << "Game Over! Result: " << resourceManager.isEndGame() << std::endl;
        return;
    }

    // Update by the managers
    mapManager.updateMap();
    enemyManager.updateEnemies();

    logicManager.playRound(resourceManager, modeManager, enemyManager, mapManager);
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
    return logicManager.isPutTower(resourceManager, towerManager, mapManager, type, position);
}

bool GameLogic::spawnTower(TowerType type, Vector2 position) {
    // Check if the tower can be placed at the given position
    return logicManager.spawnTower(resourceManager, towerManager, mapManager, type, position);
}