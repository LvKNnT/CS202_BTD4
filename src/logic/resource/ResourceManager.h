#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Resource.h"
#include "../level/DifficultyUnits.h"
#include "../level/TowerModifier.h"
#include "../level/EnemyModifier.h"

class ResourceManager {
private:
    TowerModifier towerModifier; // Manages tower modifications based on difficulty
    EnemyModifier enemyModifier; // Manages enemy modifications based on difficulty
    Difficulty currentDifficulty; // Current game difficulty

    struct DifficultyCompare {
        bool operator()(const Difficulty& a, const Difficulty& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<Difficulty, Resource, DifficultyCompare> resourceTemplates; 

public:
    ResourceManager(); 
    ResourceManager(Difficulty difficulty);
    ResourceManager(const ResourceManager& other);
    ~ResourceManager() = default;

    ResourceManager& operator=(const ResourceManager& other);

    void init();

    const Resource& getResource(Difficulty type) const;
    const TowerModifies& getTowerModifies() const;
    const EnemyModifies& getEnemyModifies() const;
};

#endif // RESOURCE_MANAGER_H