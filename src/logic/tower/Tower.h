#ifndef TOWER_H
#define TOWER_H

// We use design pattern Template Method Pattern to create towers

#include "TowerUnits.h"
#include "../GameObject.h"
#include "../attack/Attack.h"
#include "Upgrade.h"
#include "UpgradeUnits.h"
#include "../level/TowerModifies.h"

#include <memory>
#include <vector>

class Tower : public GameObject {
// should be only accessible by LogicManager and Spawner
    friend class LogicManager; 
    friend class TowerSpawner;

public:
    Tower(Vector2 position, Vector2 size, float rotation, TowerType type, int cost);
    Tower(const Tower& other);
    virtual ~Tower() = default;
    
    virtual std::unique_ptr<Tower> clone() const = 0;
    
    // Basic loaders
    virtual void loadTexture() = 0;
    void unLoad();

    // Different towers can have different behaviors when attacking
    virtual void update() = 0; // Pure virtual function for handling special attack
    virtual void setRotation(float rotation) = 0; // Pure virtual function for setting rotation
    virtual void setModifies(const TowerModifies& modifies) = 0; // Pure virtual function for setting tower modifiers
    virtual void upgrade(const UpgradeUnits& upgradeUnits, int& currentCash) = 0; // Pure virtual function for upgrading the tower

protected:
    std::vector<std::unique_ptr<Attack>> attacks; // List of attacks the tower can perform
    std::unique_ptr<Upgrade> 
        upgradeTop, 
        upgradeMiddle, 
        upgradeBottom; // Upgrades for the tower

    TowerType type; // Type of the tower
    TargetPriority targetPriority; // Target priority for the tower

    int cost; // Cost of the tower
    float upgradeCost; // Cost to upgrade the tower
};

#endif // TOWER_H