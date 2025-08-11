#include "ShurikenAttack.h"

#include "../../bullet/bullets/Shuriken.h"

#include <cmath>

ShurikenAttack::ShurikenAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff) {
    // Constructor implementation can be extended if needed
    tag = "ShurikenAttack"; 
}

std::unique_ptr<Attack> ShurikenAttack::clone() const {
    // Create a new ShurikenAttack instance with the same properties
    return std::make_unique<ShurikenAttack>(*this);
}

bool ShurikenAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const {
    // Check if the attack can hit camo targets
    if (isCamo && !(properties.canCamo || attackBuff.properties.canCamo)) return false;

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

    float buffedRange = range * attackBuff.rangeRatio + attackBuff.range;
    return distanceSq <= buffedRange * buffedRange;
}

void ShurikenAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime(); 
    }
}

void ShurikenAttack::update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) {
    // Update the attack logic, e.g., spawn a Shuriken if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        Vector2 targetPosition = enemy->getPosition();
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees

        if(properties.canTrace) {
            properties.targetEnemy = enemy; // Set the target enemy for tracing
            // std::cerr << "ShurikenAttack: Tracing enabled for enemy ID: " << enemy->getId() << std::endl;
        }
        
        attackPattern->execute(bulletManager, BulletType::Shuriken, position, {30.0f, 30.0f}, angle, 
            damage + attackBuff.damage, 
            speed * attackBuff.speedRatio,
            (pierce + attackBuff.pierce) * (attackBuff.pierceRatio + 1.0),
            lifeSpan * attackBuff.lifeSpanRatio, 
            properties + attackBuff.properties, 
            normalDebuff + attackBuff.extraNormalDebuff,
            moabDebuff + attackBuff.extraMoabDebuff,
            attackBuff,
            towerId);
        
        timer += cooldown * attackBuff.cooldownRatio; // Reset the timer after spawning
    }
}