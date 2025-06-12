#include "Enemy.h"

Enemy::Enemy(Vector2 position, Vector2 size, float rotation, BloonType type, int health, int speed, int reward, int livesLost)
    : GameObject(position, size, rotation, "Enemy"), type(type), health(health), speed(speed), reward(reward), livesLost(livesLost), trackIndex(0) {
    // Constructor implementation can be extended if needed
}

Enemy::~Enemy() = default; // Empty destructor since its a abstract class

BloonType Enemy::getType() const {
    return type;
}

int Enemy::getHealth() const {
    return health;
}

Vector2 Enemy::getPosition() const {
    return position;
}

int Enemy::getSpeed() const {
    return speed;
}

int Enemy::getTrackIndex() const {
    return trackIndex;
}

void Enemy::setTrackIndex(int index) {
    trackIndex = index;
}

void Enemy::setPosition(Vector2 position) {
    this->position = position;
}