#include "BombBliztAttack.h"

#include "../../bullet/bullets/ClusterBombBullet.h"
#include "../../bullet/bullets/RecursiveClusterBullet.h"

#include <cmath>
#include "raymath.h"

BombBliztAttack::BombBliztAttack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff)
    : Attack(range, cooldown, position, towerId, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff) {
    // Constructor implementation can be extended if needed
    tag = "BombBliztAttack"; 
}

std::unique_ptr<Attack> BombBliztAttack::clone() const {
    // Create a new BombBliztAttack instance with the same properties
    return std::make_unique<BombBliztAttack>(*this);
}

bool BombBliztAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const {
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

    float buffedRange = range * attackBuff.rangeRatio + attackBuff.range;
    return distanceSq <= buffedRange * buffedRange;
}

void BombBliztAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime(); 
    }
}

void BombBliztAttack::update(BulletManager& bulletManager, const Vector2& targetPosition, AttackBuff& attackBuff, AttackPattern& attackPattern) {
    // Update the attack logic, e.g., spawn a cluster bomb bullet if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees

        // testing
        bool isRecursive = true;

        if(isRecursive) {
            attackPattern.execute(bulletManager, BulletType::RecursiveClusterBomb, position, 
                Vector2Add({30.0f, 30.0f}, attackBuff.size),
                angle, 
                (damage + attackBuff.damage) * 500,
                speed * attackBuff.speedRatio + attackBuff.speed,
                pierce * attackBuff.pierceRatio + attackBuff.pierce,
                lifeSpan * attackBuff.lifeSpanRatio, 
                properties + attackBuff.properties, 
                normalDebuff + attackBuff.extraNormalDebuff,
                moabDebuff + attackBuff.extraMoabDebuff,
                attackBuff,
                towerId);
        }
        else {
            attackPattern.execute(bulletManager, BulletType::RecursiveClusterBomb, position, 
                Vector2Add({30.0f, 30.0f}, attackBuff.size),
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
        }
        isRecursive = !isRecursive; 

        timer = cooldown; // Reset the timer after spawning the bullet
    }
}