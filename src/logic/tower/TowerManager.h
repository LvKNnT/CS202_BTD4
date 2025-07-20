#ifndef TOWER_MANAGER_H
#define TOWER_MANAGER_H

#include "Tower.h"
#include "TowerSpawner.h"
#include "../level/TowerModifies.h"

class TowerManager {
    friend class LogicManager; // Allow LogicManager to access private members
    friend LogicInfo;

public:
    TowerManager(TowerModifies modifies = TowerModifies());
    TowerManager(const TowerManager& other); 
    ~TowerManager() = default;

    TowerManager& operator=(const TowerManager& other);

    // Methods
    void spawnTower(TowerType type, Vector2 position);
    void drawTowers() const;
    void updateTowers();
    void unLoad();

private:
    TowerModifies currentModifies; // Current tower modifies
    
    std::vector<std::unique_ptr<Tower>> towerList; // Collection to hold all active towers

    std::unique_ptr<TowerSpawner> towerSpawner; // Factory to create towers based on type

    int towerIDCounter; // Counter for ID tower
};

#endif // TOWER_MANAGER_H