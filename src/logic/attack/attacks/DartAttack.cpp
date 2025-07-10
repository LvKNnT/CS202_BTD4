#include "DartAttack.h"

DartAttack::DartAttack(float range, float cooldown, Vector2 position, int damage, int speed, int pierce, float lifeSpan)
    : Attack(range, cooldown, position, damage, speed, pierce, lifeSpan) {
    // Constructor implementation can be extended if needed
}

std::unique_ptr<Attack> DartAttack::clone() const {
    // Create a new DartAttack instance with the same properties
    return std::make_unique<DartAttack>(*this);
}

bool DartAttack::isInRange(const Vector2& targetPosition) const {
    // Check if the target is within the attack range
    float distance = sqrtf((position.x - targetPosition.x)*(position.x - targetPosition.x) + (position.y - targetPosition.y)*(position.y - targetPosition.y));
    return distance <= range; // Return true if the target is within range
}

void DartAttack::update(BulletManager& bulletManager, const Vector2& targetPosition) {
    // Update the attack logic, e.g., spawn a dart if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees
        
        bulletManager.spawnBullet(BulletType::Dart, position, {10.0f, 10.0f}, angle, damage, speed, pierce, lifeSpan);
        
        timer += cooldown; // Reset the timer after spawning
    } else {
        timer -= GetFrameTime(); // Increment the timer based on frame time
    }
}