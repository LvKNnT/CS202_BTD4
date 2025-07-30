#include "JuggernautAttack.h"

#include "../../bullet/bullets/JuggernautBullet.h"

#include <cmath>

JuggernautAttack::JuggernautAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties) {
    // Constructor implementation can be extended if needed
    tag = "JuggernautAttack"; 
}

std::unique_ptr<Attack> JuggernautAttack::clone() const {
    // Create a new JuggernautAttack instance with the same properties
    return std::make_unique<JuggernautAttack>(*this);
}

bool JuggernautAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const {
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

void JuggernautAttack::update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) {
    // Update the attack logic, e.g., spawn a juggernaut bullet if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees
        
        attackPattern.execute(bulletManager, BulletType::Juggernaut, position, {10.0f, 10.0f}, angle, 
            damage + attackBuff.damage, 
            speed * attackBuff.speedRatio, 
            pierce + attackBuff.pierce, 
            lifeSpan * attackBuff.lifeSpanRatio, 
            properties + attackBuff.properties, 
            attackBuff,
            towerId);
        
        timer += cooldown * attackBuff.cooldownRatio; // Reset the timer after spawning
    } else {
        timer -= GetFrameTime(); // Decrease the timer based on frame time
    }
}
