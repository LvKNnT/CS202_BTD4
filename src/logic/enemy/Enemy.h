#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "EnemyUnits.h"
#include "../GameObject.h"
#include "../level/EnemyModifies.h"

#include <memory>
#include <string>

// We use design pattern Template Method Pattern to create enemies

class Enemy : public GameObject {
// should be only accessible by LogicManager and Spawner
    friend class LogicManager; 
    friend class EnemySpawner;

public:
    Enemy(Vector2 position, Vector2 size, float rotation, BloonType type, int health, int speed, int reward, int livesLost);
    virtual std::unique_ptr<Enemy> clone() const = 0;
    virtual ~Enemy() = default;

    // Basic loaders
    virtual void loadTexture() = 0;
    void unLoad();
    
    // Different enemies can have different behaviors when taking damage
    virtual bool hit(int damage) = 0; // Pure virtual function for handling damage
    virtual void die() = 0; // Pure virtual function for handling death by end of track
    virtual void setRotation(float rotation) = 0; // Pure virtual function for setting rotation
    virtual void setModifies(const EnemyModifies& modifies) = 0; // Pure virtual function for setting enemy modifiers

protected:
    BloonType type;
    int health;
    int speed;
    int reward; // Reward for popping this bloon
    int livesLost; // Number of lives lost due to this bloon reaching the end

    int trackIndex; // Index of the current point in the enemy path
    int pathIndex; // Index of the path this enemy is following
};

#endif // ENEMY_H