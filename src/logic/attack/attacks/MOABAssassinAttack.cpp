#include "MOABAssassinAttack.h"

#include "../../bullet/bullets/MOABAssassinBullet.h"

#include <cmath>
#include "raymath.h"

MOABAssassinAttack::MOABAssassinAttack(Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff)
    : Attack(0.0f, 0.0f, position, towerId, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff) {
    tag = "MOABAssassinAttack"; 
}

std::unique_ptr<Attack> MOABAssassinAttack::clone() const {
    // Create a new MOABAssassinAttack instance with the same properties
    return std::make_unique<MOABAssassinAttack>(*this);
}

bool MOABAssassinAttack::isInRange(const Rectangle& rec, const float rotation, bool isCamo, AttackBuff& attackBuff) const {
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
    return distanceSq <= range * range; // No buffed range for MOAB Assassin
}

void MOABAssassinAttack::update() {
    if (timer > 0.0f) {
        timer -= GetFrameTime(); 
    }
}

void MOABAssassinAttack::update(BulletManager& bulletManager, std::shared_ptr<Enemy>& enemy, AttackBuff& attackBuff) {
    // Update the attack logic, e.g., spawn a MOAB Assassin bullet if the cooldown is over
    if (timer <= 0.0f) {
        // Calculate the rotation towards the target position
        Vector2 targetPosition = enemy->getPosition();
        float angle = atan2f(targetPosition.y - position.y, targetPosition.x - position.x);
        angle = angle * (180.0f / PI); // Convert radians to degrees
        
        attackPattern->execute(bulletManager, BulletType::MOABAssassin, position, 
            Vector2Add({40.0f, 40.0f}, attackBuff.size),
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
        
        timer = cooldown; // Reset the timer
    }
}

