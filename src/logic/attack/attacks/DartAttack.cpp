#include "DartAttack.h"

DartAttack::DartAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, bool canSeeCamo)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, canSeeCamo) {
    // Constructor implementation can be extended if needed
}

std::unique_ptr<Attack> DartAttack::clone() const {
    // Create a new DartAttack instance with the same properties
    return std::make_unique<DartAttack>(*this);
}

bool DartAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo) const {
    // Check if the attack can hit camo targets
    if (isCamo && !canSeeCamo) return false;

    // Check if the rotated rectangle (rec, rotation) collides with the circle (position, range)
    // First, get the center of the rectangle
    Vector2 rectCenter = { rec.x + rec.width / 2.0f, rec.y + rec.height / 2.0f };

    // Translate circle center to rectangle's local space
    float s = sinf(-rotation * (PI / 180.0f));
    float c = cosf(-rotation * (PI / 180.0f));
    Vector2 localCircle;
    localCircle.x = c * (position.x - rectCenter.x) - s * (position.y - rectCenter.y) + rectCenter.x;
    localCircle.y = s * (position.x - rectCenter.x) + c * (position.y - rectCenter.y) + rectCenter.y;

    // Clamp circle center to rectangle bounds
    float closestX = std::max(rec.x, std::min(localCircle.x, rec.x + rec.width));
    float closestY = std::max(rec.y, std::min(localCircle.y, rec.y + rec.height));

    // Calculate distance from circle center to closest point
    float dx = localCircle.x - closestX;
    float dy = localCircle.y - closestY;
    float distanceSq = dx * dx + dy * dy;

    return distanceSq <= range * range;
}

void DartAttack::update(BulletManager& bulletManager, const Vector2& targetPosition) {
    // Update the attack logic, e.g., spawn a dart if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees
        
        bulletManager.spawnBullet(BulletType::Dart, position, {10.0f, 10.0f}, angle, damage, speed, pierce, lifeSpan, canSeeCamo, towerId);
        
        timer += cooldown; // Reset the timer after spawning
    } else {
        timer -= GetFrameTime(); // Increment the timer based on frame time
    }
}