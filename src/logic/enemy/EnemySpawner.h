#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Enemy.h"
#include "../level/EnemyModifies.h"

#include <map>
#include <vector>

// We use design pattern Factory Method Pattern to create enemies
class EnemySpawner {
private:
    struct BloonTypeCompare {
        bool operator()(const BloonType& a, const BloonType& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };

    // For creating enemies based on type
    std::map<BloonType, std::unique_ptr<Enemy>, BloonTypeCompare> enemyTemplates;
    // for creating children enemies based on type
    std::map<BloonType, std::vector<std::unique_ptr<Enemy> >, BloonTypeCompare> enemyChildrenTemplates; 

public:
    EnemySpawner();
    EnemySpawner(const EnemySpawner& other);
    ~EnemySpawner() = default;

    EnemySpawner& operator=(const EnemySpawner& other);
    std::unique_ptr<EnemySpawner> clone() const;

    void init();

    // Returns a unique_ptr to a new Enemy of the given type
    std::unique_ptr<Enemy> getEnemy(BloonType type, Vector2 position, EnemyModifies modifies);
    std::vector<std::unique_ptr<Enemy> > getChildrenEnemies(BloonType type, Vector2 position, EnemyModifies modifies);
};

#endif // ENEMYSPAWNER_H