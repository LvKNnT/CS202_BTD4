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
    // For creating children enemies based on type
    std::map<BloonType, std::vector<std::unique_ptr<Enemy> >, BloonTypeCompare> enemyChildrenTemplates; 
    // For creating regrow enemies
    std::map<BloonType, std::unique_ptr<Enemy> , BloonTypeCompare> regrowEnemyTemplates;

    const float regrowTime = 3.0f; // Time for regrow enemy to regrow

public:
    EnemySpawner();
    EnemySpawner(const EnemySpawner& other);
    ~EnemySpawner() = default;

    EnemySpawner& operator=(const EnemySpawner& other);
    std::unique_ptr<EnemySpawner> clone() const;

    void init();

    // Returns a unique_ptr to a new Enemy of the given type
    std::unique_ptr<Enemy> getEnemy(BloonType type, BloonProperties properties, Vector2 position, int pathIndex, int enemyId, EnemyModifies modifies);
    std::vector<std::unique_ptr<Enemy> > getChildrenEnemies(Enemy* enemy, int round, EnemyModifies modifies);
    void getRegrowEnemy(std::unique_ptr<Enemy>& enemy, EnemyModifies modifies);
};

#endif // ENEMYSPAWNER_H