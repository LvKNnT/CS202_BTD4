#include "CaltropsAttack.h"

#include "../../bullet/bullets/CaltropsBullet.h"

#include <cmath>

CaltropsAttack::CaltropsAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff) {
    // Constructor implementation can be extended if needed
    tag = "CaltropsAttack"; 
}

std::unique_ptr<Attack> CaltropsAttack::clone() const {
    // Create a new CaltropsAttack instance with the same properties
    return std::make_unique<CaltropsAttack>(*this);
}

bool CaltropsAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const {
    // Always attacking

    return true;
}

void CaltropsAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime(); 
    }
}

void CaltropsAttack::update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff) {
    // Update the attack logic, e.g., spawn a Shuriken if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        rotation = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        rotation = rotation * (180.0f / PI); // Convert radians to degrees
        
        attackPattern->execute(bulletManager, BulletType::Caltrops, position, {20.0f, 20.0f}, rotation, 
            damage + attackBuff.damage, 
            speed * attackBuff.speedRatio,
            (pierce + attackBuff.pierce) * (attackBuff.pierceRatio + 1.0),
            lifeSpan * attackBuff.lifeSpanRatio, 
            properties + attackBuff.properties, 
            normalDebuff + attackBuff.extraNormalDebuff,
            moabDebuff + attackBuff.extraMoabDebuff,
            attackBuff,
            towerId);

        rotation = fmod(rotation, 360.0f); // Ensure rotation is within [0, 360)
        
        timer += cooldown * attackBuff.cooldownRatio; // Reset the timer after spawning
    }
}

float CaltropsAttack::isRotateTower() {
    if(rotation < 0.0f) {
        return -1.0f; // Use default rotation
    }
    float rot = rotation;
    rotation = -1.0f;
    return rot;
}