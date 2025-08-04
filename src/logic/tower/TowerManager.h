#ifndef TOWER_MANAGER_H
#define TOWER_MANAGER_H

#include "Tower.h"
#include "TowerSpawner.h"
#include "../level/TowerModifies.h"

#include "../skill/Skill.h"

class TowerManager {
    friend class LogicManager; // Allow LogicManager to access private members
    friend LogicInfo;

public:
    TowerManager(TowerModifies modifies = TowerModifies());
    TowerManager(const TowerManager& other); 
    ~TowerManager() = default;

    TowerManager& operator=(const TowerManager& other);

    // Methods
    void pickTower(Vector2 position);
    void unPickTower();
    void spawnTower(TowerType type, Vector2 position);
    void spawnPutTower(TowerType type, Vector2 position);
    void unPutTower();
    void spawnTower(TowerType type, Vector2 position, float rotation);
    LogicInfo getInfo() const;
    LogicInfo getInfoTower(TowerType type) const;
    LogicInfo getInfoTower(Vector2 position) const;
    void chooseNextPriority();
    void chooseNextPriority(Vector2 position);
    void choosePreviousPriority();
    void choosePreviousPriority(Vector2 position);
    int sellTower();

    void drawTowers() const;
    void updateTowers();

    // save/load
    void save(const std::string& filePath) const;
    void load(const std::string& filePath);

private:
    TowerModifies currentModifies; // Current tower modifies
    
    std::vector<std::shared_ptr<Tower>> towerList; // Collection to hold all active towers
    std::weak_ptr<Tower> lastPickedTower;
    std::unique_ptr<Tower> putTower;

    std::unique_ptr<TowerSpawner> towerSpawner; // Factory to create towers based on type

    int towerIDCounter; // Counter for ID tower

    // Helper methods
    std::weak_ptr<Tower> getTowerFromPosition(Vector2 position) const;
};

#endif // TOWER_MANAGER_H