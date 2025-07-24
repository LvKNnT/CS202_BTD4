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
    // init(difficulty, mapType, modeType); // same same but different
    init(mapType);
    init(difficulty);
    init(modeType);

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

void GameLogic::init(MapType mapType) {
    mapManager.loadMap(mapType);
}

void GameLogic::init(Difficulty difficulty) {
    resourceManager.initResource(difficulty);

    enemyManager = EnemyManager(resourceManager.getEnemyModifies());
    towerManager = TowerManager(resourceManager.getTowerModifies());
}

void GameLogic::init(ModeType modeType) {
    modeManager.setMode(modeType);
}

void GameLogic::update() {
    for(int i = 0; i < (isTickFast ? 3 : 1); ++i) {
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

bool GameLogic::isUpgradeTower(Vector2 position, UpgradeUnits upgradeUnits) const {
    // Check if the tower can be upgraded at the given position
    return logicManager.isUpgradeTower(resourceManager, towerManager, position, upgradeUnits);
}

bool GameLogic::upgradeTower(Vector2 position, UpgradeUnits upgradeUnits) {
    // Upgrade the tower at the given position
    return logicManager.upgradeTower(resourceManager, towerManager, position, upgradeUnits);
}

LogicInfo GameLogic::getInfoTower(TowerType type) const {
    return towerManager.getInfoTower(type);
}

LogicInfo GameLogic::getInfoTower(Vector2 position) const {
    return towerManager.getInfoTower(position);
}

void GameLogic::chooseNextPriority(Vector2 position) {
    towerManager.chooseNextPriority(position);
}

void GameLogic::choosePreviousPriority(Vector2 position) {
    towerManager.choosePreviousPriority(position);
}

// same same but different
void GameLogic::setAutoPlay(bool autoPlay) {
    logicManager.setAutoPlay(modeManager, autoPlay);
}

void GameLogic::activeAutoPlay() {
    setAutoPlay(true);
}

void GameLogic::unactiveAutoPlay() {
    setAutoPlay(false);
}

// same same but different
void GameLogic::setTickFast(bool isTickFast) {
    this->isTickFast = isTickFast;
}

void GameLogic::activeTickFast() {
    setTickFast(true);
}

void GameLogic::unactiveTickFast() {
    setTickFast(false);
}

LogicInfo GameLogic::getInfoResource() const {
    return resourceManager.getInfo();
}