#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Resource.h"
#include "../level/DifficultyUnits.h"
#include "../level/TowerModifier.h"
#include "../level/EnemyModifier.h"
#include "ResourceSpawner.h"

class ResourceManager {
    friend class LogicManager; // Allow LogicManager to access private members

private:
    TowerModifier towerModifier; // Manages tower modifications based on difficulty
    EnemyModifier enemyModifier; // Manages enemy modifications based on difficulty
    ResourceSpawner resourceSpawner;
    Difficulty currentDifficulty; // Current game difficulty
    Resource currentResource; // Current resource state

public:
    ResourceManager() = default; 
    ~ResourceManager() = default;

    void initResource(Difficulty difficulty);
    Resource& getResource();
    const TowerModifies& getTowerModifies() const;
    const EnemyModifies& getEnemyModifies() const;

    int isEndGame() const;
    LogicInfo getInfo() const;

    // save/load
    void save(const std::string& filePath, bool isRoundEnd) const;
    void load(const std::string& filePath);
};

#endif // RESOURCE_MANAGER_H