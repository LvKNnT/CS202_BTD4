#include "Bullet.h"

Bullet::Bullet(Vector2 position, Vector2 size, float rotation, BulletType type, int damage, int speed, int pierce, float lifeSpan)
    : GameObject(position, size, rotation, "Bullet"), type(type), damage(damage), speed(speed), pierce(pierce), lifeSpan(lifeSpan) {
    // Constructor implementation can be extended if needed
}

void Bullet::unLoad() {
    UnloadTexture(texture); 
}