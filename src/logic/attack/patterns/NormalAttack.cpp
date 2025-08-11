#include "NormalAttack.h"

NormalAttack::NormalAttack(MapManager* mapManager)
    : AttackPattern(mapManager) {
    // No use
}

std::unique_ptr<AttackPattern> NormalAttack::clone() const {
    // Create a new NormalAttack instance
    return std::make_unique<NormalAttack>(*this);
}

void NormalAttack::execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float& rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) {
    // Create a bullet with the specified properties
    bulletManager.spawnBullet(type, position, size, rotation, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff, attackBuff, towerId);
}