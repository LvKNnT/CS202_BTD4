#include "SubmergeAttack.h"

#include "../../bullet/bullets/Dart.h"

#include <cmath>
#include "raymath.h"

SubmergeAttack::SubmergeAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff) {
    // Constructor implementation can be extended if needed
    tag = "SubmergeAttack"; 
}

std::unique_ptr<Attack> SubmergeAttack::clone() const {
    // Create a new SubmergeAttack instance with the same properties
    return std::make_unique<SubmergeAttack>(*this);
}

bool SubmergeAttack::isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const {
    // Check if the attack can hit camo targets
    if (enemy.getProperties().isCamo && !(properties.canCamo || attackBuff.properties.canCamo)) return false;

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

void SubmergeAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime(); 
    }
}

void SubmergeAttack::update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) {
    // Update the attack logic, e.g., spawn a dart if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        Vector2 targetPosition = enemy->getPosition();
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees
        
        if(properties.canTrace) {
            properties.targetEnemy = enemy; // Set the target enemy for tracing
            // std::cerr << "Dart bullet is tracing enemy with ID: " << enemy->getId() << std::endl;
        }
        
        attackPattern->execute(bulletManager, BulletType::Submerge, position, 
            {(range * attackBuff.rangeRatio + attackBuff.range) * 2, (range * attackBuff.rangeRatio + attackBuff.range) * 2},
            angle, 
            damage + attackBuff.damage, 
            0, 
            pierce * attackBuff.pierceRatio + attackBuff.pierce, 
            std::min(lifeSpan * attackBuff.lifeSpanRatio, cooldown * attackBuff.cooldownRatio), 
            properties + attackBuff.properties, 
            normalDebuff + attackBuff.extraNormalDebuff,
            moabDebuff + attackBuff.extraMoabDebuff,
            attackBuff,
            towerId);
        
        timer += cooldown * attackBuff.cooldownRatio; // Reset the timer after spawning
    }
}