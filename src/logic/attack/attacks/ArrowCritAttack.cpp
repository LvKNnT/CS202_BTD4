#include "ArrowCritAttack.h"

#include "../../bullet/bullets/Arrow.h"
#include "../../bullet/bullets/ArrowCrit.h"

#include <cmath>

ArrowCritAttack::ArrowCritAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, int maxCounter)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties), counter(0), maxCounter(maxCounter) {
    // Constructor implementation can be extended if needed
    tag = "ArrowCritAttack";
}

std::unique_ptr<Attack> ArrowCritAttack::clone() const {
    // Create a new ArrowCritAttack instance with the same properties
    return std::make_unique<ArrowCritAttack>(*this);
}

bool ArrowCritAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const {
    // Check if the attack can hit camo targets
    if (isCamo && !(properties.canCamo || attackBuff.properties.canCamo)) return false;

    // Check if the rotated rectangle (rec, rotation) collides with the circle (position, range)
    Vector2 rectCenter = { rec.x + rec.width / 2.0f, rec.y + rec.height / 2.0f };

    float s = sinf(-rotation * (PI / 180.0f));
    float c = cosf(-rotation * (PI / 180.0f));
    Vector2 localCircle;
    localCircle.x = c * (position.x - rectCenter.x) - s * (position.y - rectCenter.y) + rectCenter.x;
    localCircle.y = s * (position.x - rectCenter.x) + c * (position.y - rectCenter.y) + rectCenter.y;

    float closestX = std::max(rec.x, std::min(localCircle.x, rec.x + rec.width));
    float closestY = std::max(rec.y, std::min(localCircle.y, rec.y + rec.height));

    float dx = localCircle.x - closestX;
    float dy = localCircle.y - closestY;
    float distanceSq = dx * dx + dy * dy;

    float buffedRange = range + attackBuff.range;
    return distanceSq <= buffedRange * buffedRange;
}

void ArrowCritAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime();
    }
}

void ArrowCritAttack::update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) {
    // Update the attack logic, e.g., spawn an arrow or arrow crit bullet if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees

        if (counter < maxCounter) {
            attackPattern.execute(bulletManager, BulletType::Arrow, position, {10.0f, 10.0f}, angle,
                damage + attackBuff.damage,
                speed * attackBuff.speedRatio,
                pierce + attackBuff.pierce,
                lifeSpan * attackBuff.lifeSpanRatio,
                properties + attackBuff.properties,
                attackBuff,
                towerId);
            counter++;
        } else {
            attackPattern.execute(bulletManager, BulletType::ArrowCrit, position, {10.0f, 10.0f}, angle,
                (damage + attackBuff.damage) * 10,
                speed * attackBuff.speedRatio,
                pierce + attackBuff.pierce,
                lifeSpan * attackBuff.lifeSpanRatio,
                properties + attackBuff.properties,
                attackBuff,
                towerId);
            counter = 0; // Reset counter after firing a crit
        }

        timer += cooldown * attackBuff.cooldownRatio; // Reset the timer after spawning
    }
}

