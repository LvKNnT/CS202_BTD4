#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "Bullet.h"
#include "BulletSpawner.h"

#include <vector>
#include <memory>

// This class manages all bullets in the game
class BulletManager {
    friend class LogicManager; // Allow LogicManager to access private members

public:
    BulletManager();
    BulletManager(const BulletManager& other);
    ~BulletManager() = default;

    BulletManager& operator=(const BulletManager& other);

    // Methods
    void spawnBullet(BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, int towerId);
    void drawBullets() const;
    void unLoad();

private:
    // Instances
    std::unique_ptr<BulletSpawner> bulletSpawner; // Factory to create bullets based on type

    // Collection to hold all active bullets
    std::vector<std::unique_ptr<Bullet>> bulletList; 
};


#endif // BULLETMANAGER_H