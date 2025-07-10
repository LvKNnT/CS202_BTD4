#ifndef BULLET_H
#define BULLET_H

#include "BulletUnits.h"
#include "../GameObject.h"

#include <memory>
#include <string>

// We use design pattern Template Method Pattern to create bullets

class Bullet : public GameObject {
    // should be only accessible by LogicManager and Spawner
    friend class LogicManager;
    friend class BulletSpawner;

public:
    Bullet(Vector2 position, Vector2 size, float rotation, BulletType type, int damage, int speed, int pierce, float lifeSpan);
    virtual std::unique_ptr<Bullet> clone() const = 0;
    virtual ~Bullet() = default;

    // Basic loaders
    virtual void loadTexture() = 0;
    void unLoad();

    // Different bullets can have different behaviors when hitting targets
    virtual bool hit(int damage) = 0; // Pure virtual function for handling hit
    virtual void setRotation(float rotation) = 0; // Pure virtual function for setting rotation
    virtual void die() = 0; // Pure virtual function for handling death or end of life

protected:
    BulletType type;
    int damage; // Damage dealt by the bullet
    int speed; // Speed of the bullet
    int pierce; // Number of targets the bullet can pierce through
    float lifeSpan; // Life span of the bullet in frames

    // Position and rotation for movement
    Vector2 position; // Position of the bullet
    float rotation; // Rotation angle for the bullet
};

#endif  // BULLET_H