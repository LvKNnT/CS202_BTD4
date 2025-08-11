#include "OctupleAttack.h"

OctupleAttack::OctupleAttack(MapManager* mapManager)
    : AttackPattern(mapManager) {
    // No use
}

std::unique_ptr<AttackPattern> OctupleAttack::clone() const {
    return std::make_unique<OctupleAttack>(*this);
}

void OctupleAttack::execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float& rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) {
    // Create 8 bullets with the specified properties
    for (int i = -4; i <= 4; ++i) {
        if(i == 0) continue;
        float angleOffset = i * 15.0f; // Adjust the angle offset as needed
        bulletManager.spawnBullet(type, position, size, rotation + angleOffset, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff, attackBuff, towerId);
    }
}