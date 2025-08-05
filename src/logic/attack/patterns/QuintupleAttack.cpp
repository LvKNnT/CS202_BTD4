#include "QuintupleAttack.h"

std::unique_ptr<AttackPattern> QuintupleAttack::clone() const {
    return std::make_unique<QuintupleAttack>(*this);
}

void QuintupleAttack::execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) {
    // Create 5 bullets with the specified properties
    for (int i = -2; i <= 2; i++) {
        float angleOffset = i * 15.0f; // Adjust the angle offset as needed
        bulletManager.spawnBullet(type, position, size, rotation + angleOffset, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff, attackBuff, towerId);
    }
}