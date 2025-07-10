#ifndef TOWER_SPAWNER_H
#define TOWER_SPAWNER_H

#include "Tower.h"
#include "../level/TowerModifies.h"

// We use design pattern Factory Method Pattern to create towers
class TowerSpawner {
private:
    struct TowerTypeCompare {
        bool operator()(const TowerType& a, const TowerType& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };

    // For creating towers based on type
    std::map<TowerType, std::unique_ptr<Tower>, TowerTypeCompare> towerTemplates;

public:
    TowerSpawner();
    TowerSpawner(const TowerSpawner& other);
    ~TowerSpawner() = default;

    TowerSpawner& operator=(const TowerSpawner& other);
    std::unique_ptr<TowerSpawner> clone() const;

    void init();

    // Returns a unique_ptr to a new Tower of the given type
    std::unique_ptr<Tower> getTower(TowerType type, Vector2 position, const TowerModifies& modifies);
};

#endif // TOWER_SPAWNER_H