#include "Enemy.h"

Enemy::Enemy(Vector2 position, Vector2 size, float rotation, BloonType type, int health, int speed, int reward, int livesLost)
    : GameObject(position, size, rotation, "Enemy"), type(type), health(health), speed(speed), reward(reward), livesLost(livesLost), trackIndex(0), pathIndex(0), properties(BloonProperties()), regrowLimit(type), regrowTimer(0.0f) {
    // Constructor implementation can be extended if needed
}

void Enemy::unLoad() {
    UnloadTexture(texture);
}