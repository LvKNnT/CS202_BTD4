#ifndef TOWER_H
#define TOWER_H

// We use design pattern Template Method Pattern to create towers

#include "TowerUnits.h"
#include "../GameObject.h"
#include "../attack/Attack.h"
#include "../attack/AttackPattern.h"
#include "Upgrade.h"
#include "UpgradeUnits.h"
#include "UpgradeTextureHandler.h"
#include "../level/TowerModifies.h"
#include "../LogicInfo.h"

// Some pre-declarations
class Skill;

#include <memory>
#include <vector>

class Tower : public GameObject {
// should be only accessible by LogicManager and Spawner
    friend class LogicManager; 
    friend class TowerManager;
    friend class TowerSpawner;
    friend class SkillSpawner;
    friend class SkillFriendAccess; 

public:
    Tower(Vector2 position, Vector2 size, float rotation, TowerType type, int cost);
    Tower(const Tower& other);
    virtual ~Tower() = default;
    
    Tower& operator=(const Tower& other) = default;
    virtual std::unique_ptr<Tower> clone() const = 0;
    
    // Basic loaders
    virtual void loadTexture() = 0;

    // Different towers can have different behaviors when attacking
    virtual void update() = 0; // Pure virtual function for handling special attack
    virtual void drawRange() const = 0;
    virtual void drawPut() const = 0;
    virtual void setRotation(float rotation) = 0; 
    virtual void setModifies(const TowerModifies& modifies) = 0; 
    virtual LogicInfo getInfo() = 0; // Pure virtual function for UI info

protected:
    std::vector<std::unique_ptr<Attack>> attacks; // List of attacks the tower can perform
    std::unique_ptr<Upgrade> 
        upgradeTop, 
        upgradeMiddle, 
        upgradeBottom; // Upgrades for the tower
    UpgradeTextureHandler upgradeTextureHandler; // Handles the textures for upgrades

    TowerType type; // Type of the tower
    TargetPriority targetPriority; 
    AttackBuff attackBuff; 
    std::unique_ptr<Skill> skill; // Skill for the tower
    std::vector<std::unique_ptr<Skill> > passiveSkills; // Passive skill for the tower

    int cost; 
    float upgradeCost;

    int towerId; 
    int popCount; 
    LogicInfo info;
};

#endif // TOWER_H