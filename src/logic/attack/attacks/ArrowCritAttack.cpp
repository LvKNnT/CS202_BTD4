#include "ArrowCritAttack.h"

#include "../../bullet/bullets/Arrow.h"
#include "../../bullet/bullets/ArrowCrit.h"

#include <cmath>
#include "raymath.h"

ArrowCritAttack::ArrowCritAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, int maxCounter)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff), counter(0), maxCounter(maxCounter) {
    // Constructor implementation can be extended if needed
    tag = "ArrowCritAttack";
}

std::unique_ptr<Attack> ArrowCritAttack::clone() const {
    // Create a new ArrowCritAttack instance with the same properties
    return std::make_unique<ArrowCritAttack>(*this);
}

bool ArrowCritAttack::isInRange(const Rectangle& rec, const float rotation, AttackBuff& attackBuff, const Enemy &enemy) const {
    // Check if the attack can hit camo targets
    if (enemy.getProperties().isCamo && !(properties.canCamo || attackBuff.properties.canCamo)) return false;
    
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

    float buffedRange = range * attackBuff.rangeRatio + attackBuff.range;
    return distanceSq <= buffedRange * buffedRange;
}

void ArrowCritAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime();
    }
}

void ArrowCritAttack::update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) {
    // Update the attack logic, e.g., spawn an arrow or arrow crit bullet if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        Vector2 targetPosition = enemy->getPosition();
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees

        if (counter < maxCounter) {
            attackPattern->execute(bulletManager, BulletType::Arrow, position, 
                Vector2Add({50.0f, 12.0f}, attackBuff.size),
                angle,
                damage + attackBuff.damage, 
                speed * attackBuff.speedRatio + attackBuff.speed, 
                pierce * attackBuff.pierceRatio + attackBuff.pierce, 
                lifeSpan * attackBuff.lifeSpanRatio, 
                properties + attackBuff.properties, 
                normalDebuff + attackBuff.extraNormalDebuff,
                moabDebuff + attackBuff.extraMoabDebuff,
                attackBuff,
                towerId);
            counter++;
        } else {
            attackPattern->execute(bulletManager, BulletType::ArrowCrit, position, 
                Vector2Add({50.0f, 15.0f}, attackBuff.size),
                angle,
                (damage + attackBuff.damage) * 10,
                speed * attackBuff.speedRatio + attackBuff.speed, 
                pierce * attackBuff.pierceRatio + attackBuff.pierce, 
                lifeSpan * attackBuff.lifeSpanRatio, 
                properties + attackBuff.properties, 
                normalDebuff + attackBuff.extraNormalDebuff,
                moabDebuff + attackBuff.extraMoabDebuff,
                attackBuff,
                towerId);
            counter = 0; // Reset counter after firing a crit
        }

        timer += cooldown * attackBuff.cooldownRatio; // Reset the timer after spawning
    }
}

