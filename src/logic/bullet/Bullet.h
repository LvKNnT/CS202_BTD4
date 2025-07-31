#ifndef BULLET_H
#define BULLET_H

#include "BulletUnits.h"
#include "../GameObject.h"
#include "../attack/AttackUnits.h"
#include "../enemy/Enemy.h"

#include <memory>
#include <string>
#include <set>
#include <vector>

// We use design pattern Template Method Pattern to create bullets

class Bullet : public GameObject {
    // should be only accessible by LogicManager and Spawner
    friend class LogicManager;
    friend class BulletSpawner;

public:
    Bullet(BulletType type);
    virtual std::unique_ptr<Bullet> clone() const = 0;
    virtual ~Bullet() = default;

    // Basic loaders
    virtual void loadTexture() = 0;

    // Different bullets can have different behaviors when hitting targets
    virtual void init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff attackBuff, int towerId) = 0;
    virtual bool hit(int damage) = 0; // Pure virtual function for handling hit
    virtual int run() = 0; // Pure virtual function for running the bullet logic
    virtual void update(std::vector<std::unique_ptr<Enemy>>& enemyList) = 0; // Pure virtual function for updating the bullet tracing
    virtual void setRotation(float rotation) = 0; // Pure virtual function for setting rotation
    virtual int die() = 0; // Pure virtual function for handling death or end of life
    virtual std::vector<std::unique_ptr<Bullet>> getChild() = 0;

protected:
    BulletType type;
    int damage; // Damage dealt by the bullet
    int speed; // Speed of the bullet
    int pierce; // Number of targets the bullet can pierce through
    float lifeSpan; // Life span of the bullet in frames
    BulletProperties properties; // Properties of the bullet, such as canHitCamo
    AttackBuff attackBuff; // Buffs applied to the bullet, such as range, damage, etc.

    // Position and rotation for movement
    Vector2 position; // Position of the bullet
    float rotation; // Rotation angle for the bullet

    int towerId; // ID of the tower that created this bullet, if applicable
    std::set<int> hitEnemies; // Set of enemy IDs that this bullet has hit
};

#endif  // BULLET_H