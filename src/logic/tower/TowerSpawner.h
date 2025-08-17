#ifndef TOWER_SPAWNER_H
#define TOWER_SPAWNER_H

#include "Tower.h"
#include "../level/TowerModifies.h"
#include "../LogicInfo.h"
#include "../hero/Hero.h"

// We use design pattern Factory Method Pattern to create towers
class TowerSpawner {
    friend class TowerManager; // Allow TowerManager to access private members
    
private:
    struct TowerTypeCompare {
        bool operator()(const TowerType& a, const TowerType& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };

    // For creating towers based on type
    std::map<TowerType, std::unique_ptr<Tower>, TowerTypeCompare> towerTemplates;

    TowerModifies currentModifies; 
    std::unique_ptr<Hero> hero; // Current hero
public:
    TowerSpawner();
    TowerSpawner(TowerModifies modifies);
    TowerSpawner(TowerModifies modifies, HeroType heroType);
    TowerSpawner(const TowerSpawner& other);
    ~TowerSpawner() = default;

    TowerSpawner& operator=(const TowerSpawner& other);
    std::unique_ptr<TowerSpawner> clone() const;

    void init();
    void init(TowerModifies modifies);

    // Returns a unique_ptr to a new Tower of the given type
    std::unique_ptr<Tower> getTower(TowerType type, Vector2 position, int towerID, const TowerModifies& modifies);
    std::unique_ptr<Tower> getPutTower(TowerType type, Vector2 position, const TowerModifies& modifies);
    std::unique_ptr<Tower> getTower(TowerType type, Vector2 position, float rotation, int towerID, const TowerModifies& modifies);
    int getRangeTower(TowerType type) const;
    LogicInfo getInfoTower(TowerType type, const TowerModifies& modifies) const;
    Rectangle getBoundingBox(TowerType type, Vector2 position) const;
};

#endif // TOWER_SPAWNER_H