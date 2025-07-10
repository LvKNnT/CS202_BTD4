#ifndef BULLETSPAWNER_H
#define BULLETSPAWNER_H

#include "Bullet.h"

#include <map>

// We use design pattern Factory Method Pattern to create bullets
class BulletSpawner {
private:
    struct BulletTypeCompare {
        bool operator()(const BulletType& a, const BulletType& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<BulletType, std::unique_ptr<Bullet>, BulletTypeCompare> bulletTemplates;

public:
    BulletSpawner();
    BulletSpawner(const BulletSpawner& other);
    ~BulletSpawner() = default;

    BulletSpawner& operator=(const BulletSpawner& other);
    std::unique_ptr<BulletSpawner> clone() const;

    void init();

    // Returns a unique_ptr to a new Bullet of the given type
    std::unique_ptr<Bullet> getBullet(BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan);
};

#endif // BULLETSPAWNER_H