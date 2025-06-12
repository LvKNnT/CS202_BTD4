#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "EnemyUnits.h"
#include "../GameObject.h"
#include <memory>
#include <string>

// We use design pattern Abstract Factory to create enemies

class Enemy : public GameObject {
public:
    Enemy(Vector2 position, Vector2 size, float rotation, BloonType type, int health, int speed, int reward, int livesLost);
    virtual std::unique_ptr<Enemy> clone() const = 0;
    virtual ~Enemy();

    // Basic getters
    BloonType getType() const;
    int getHealth() const;

    // getters and setters for running
    Vector2 getPosition() const;
    int getSpeed() const;
    int getTrackIndex() const;
    void setTrackIndex(int index);
    void setPosition(Vector2 position);
    
    // Different enemies can have different behaviors when taking damage
    virtual bool hit(int damage) = 0; // Pure virtual function for handling damage
    virtual void die() = 0; // Pure virtual function for handling death by end of track
protected:
    BloonType type;
    int health;
    int speed;
    int reward; // Reward for popping this bloon
    int livesLost; // Number of lives lost due to this bloon reaching the end

    int trackIndex; // Index of the current point in the enemy path
};

#endif // ENEMY_H