#include "GameLogic.h"
#include <fstream>
#include <filesystem>

void GameLogic::init() {
    // testing, should be jajaja whenever enter a new game
    std::cerr << "init jajaja" << std::endl;

    // Currently working on create new game 
    // parameters
    const Difficulty difficulty = Difficulty::Medium; // Default difficulty for testing
    const MapType mapType = MapType::MonkeyLane; // Default map type for testing
    const ModeType modeType = ModeType::Alternative; // Default mode type for testing

    // stimulate what will happen in the game
    // init(difficulty, mapType, modeType); // same same but different
    init(mapType);
    init(difficulty);
    init(modeType);

    //putTower(TowerType::DartMonkey, {200.0f, 230.0f}); // draging tower
    putTower(TowerType::DartMonkey, {125.0f, 230.0f}); // draging tower
    spawnTower(); // default state on the map
    
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
        }

        // Update by the managers
        mapManager.updateMap();
        enemyManager.updateEnemies();

        if(resourceManager.isEndGame() == 0 && logicManager.playRound(resourceManager, modeManager, enemyManager, mapManager)) {
            autoSave(); 
        }

        logicManager.updateBulletsHitEnemies(bulletManager, enemyManager, towerManager, mapManager, resourceManager);
        logicManager.updateEnemies(enemyManager, mapManager, resourceManager);
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

int GameLogic::isEndGame() const {
    return resourceManager.isEndGame();
}

void GameLogic::pickTower(Vector2 position) {
    towerManager.pickTower(position);
}

void GameLogic::unPickTower() {
    towerManager.unPickTower();
}

void GameLogic::putTower(TowerType type, Vector2 position) {
    towerManager.spawnPutTower(type, position);
    logicManager.isSpawnTower(resourceManager, towerManager, mapManager);
}

void GameLogic::unPutTower() {
    towerManager.unPutTower();
}

bool GameLogic::spawnTower() {
    // Check if the tower can be placed at the given position
    return logicManager.spawnTower(resourceManager, towerManager, mapManager);
}

bool GameLogic::isUpgradeTower(UpgradeUnits upgradeUnits) const {
    // Check if the tower can be upgraded at the given position
    return logicManager.isUpgradeTower(resourceManager, towerManager, upgradeUnits);
}

bool GameLogic::upgradeTower(UpgradeUnits upgradeUnits) {
    // Upgrade the tower at the given position
    return logicManager.upgradeTower(resourceManager, towerManager, upgradeUnits);
}

void GameLogic::sellTower() {
    // Sell the currently picked tower
    logicManager.sellTower(resourceManager, towerManager);
}

LogicInfo GameLogic::getInfoTower() const {
    return towerManager.getInfo();
}

LogicInfo GameLogic::getInfoTower(TowerType type) const {
    return towerManager.getInfoTower(type);
}

void GameLogic::chooseNextPriority() {
    towerManager.chooseNextPriority();
}

void GameLogic::choosePreviousPriority() {
    towerManager.choosePreviousPriority();
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

void GameLogic::autoSave() const {
    std::string saveFilePath = savePath + "autosave.txt";
    std::cerr << "Auto-saving to: " << saveFilePath << std::endl;

    // reset autosave file
    std::fstream saveFile(saveFilePath, std::ios::out | std::ios::trunc);
    if (saveFile.is_open()) {
        saveFile.close();
    } else {
        std::cerr << "Error: Failed to open autosave file for resetting." << std::endl;
    }

    mapManager.save(saveFilePath);
    resourceManager.save(saveFilePath);
    modeManager.save(saveFilePath);
    towerManager.save(saveFilePath);
}

void GameLogic::loadAutoSave() {
    std::string saveFilePath = savePath + "autosave.txt";
    std::cerr << "Loading autosave from: " << saveFilePath << std::endl;

    if (!std::filesystem::exists(saveFilePath)) {
        std::cerr << "Autosave file does not exist: " << saveFilePath << std::endl;
        return;
    }

    mapManager.load(saveFilePath);
    resourceManager.load(saveFilePath);
    modeManager.load(saveFilePath);
    towerManager.load(saveFilePath);
}

void GameLogic::saveGame() const {
    std::string saveFilePath = savePath + "save" + std::to_string(static_cast<int>(mapManager.getMapType())) + ".txt";
    std::cerr << "Saving game to: " << saveFilePath << std::endl;

    // reset save file
    std::fstream saveFile(saveFilePath, std::ios::out | std::ios::trunc);
    if (saveFile.is_open()) {
        saveFile.close();
    } else {
        std::cerr << "Error: Failed to open save file for resetting." << std::endl;
    }

    mapManager.save(saveFilePath);
    resourceManager.save(saveFilePath);
    modeManager.save(saveFilePath);
    towerManager.save(saveFilePath);
}

void GameLogic::loadGame(MapType type) {
    std::string saveFilePath = savePath + "save" + std::to_string(static_cast<int>(type)) + ".txt";
    std::cerr << "Loading game from: " << saveFilePath << std::endl;

    if (!std::filesystem::exists(saveFilePath)) {
        std::cerr << "Save file does not exist: " << saveFilePath << std::endl;
        return;
    }

    mapManager.load(saveFilePath);

    resourceManager.load(saveFilePath);
    enemyManager = EnemyManager(resourceManager.getEnemyModifies());
    towerManager = TowerManager(resourceManager.getTowerModifies());
    towerManager.load(saveFilePath);

    modeManager.load(saveFilePath);
}