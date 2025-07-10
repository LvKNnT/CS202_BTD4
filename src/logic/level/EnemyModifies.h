#ifndef ENEMEYMODIFIES_H
#define ENEMEYMODIFIES_H

// This class shows the modifications that can be applied to an enemy
class EnemyModifies {
public:
    EnemyModifies(float speed = 1.0f, float health = 1.0f, float reward = 1.0f)
        : speed(speed), health(health), reward(reward) {}

    // Copy constructor
    EnemyModifies(const EnemyModifies& other)
        : speed(other.speed), health(other.health), reward(other.reward) {}

    // Assignment operator
    EnemyModifies& operator=(const EnemyModifies& other) {
        if (this != &other) {
            speed = other.speed;
            health = other.health;
            reward = other.reward;
        }
        return *this;
    }

    float speed; // Speed of the enemy
    float health; // Health of the enemy
    float reward; // Reward for popping this enemy
};

#endif // ENEMEYMODIFIES_H