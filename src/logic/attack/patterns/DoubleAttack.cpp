#include "DoubleAttack.h"

std::unique_ptr<AttackPattern> DoubleAttack::clone() const {
    return std::make_unique<DoubleAttack>(*this);
}

void DoubleAttack::execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) {
    // Create 2 bullets with the specified properties
    for (int i = -1; i <= 1; i += 2) {
        float angleOffset = i * 15.0f; // Adjust the angle offset as needed
        bulletManager.spawnBullet(type, position, size, rotation + angleOffset, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff, attackBuff, towerId);
    }
}