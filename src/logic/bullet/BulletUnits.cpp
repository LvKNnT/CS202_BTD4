#include "BulletUnits.h"
#include "../enemy/Enemy.h"

BulletProperties& BulletProperties::operator+= (const BulletProperties& other) {
    canLead = canLead || other.canLead;
    canBlack = canBlack || other.canBlack;
    canWhite = canWhite || other.canWhite;
    canFrozen = canFrozen || other.canFrozen;
    canCamo = canCamo || other.canCamo;
    canPurple = canPurple || other.canPurple;
    canStripCamo = canStripCamo || other.canStripCamo;

    if(other.canTrace && !other.targetEnemy.expired()) {
        targetEnemy = other.targetEnemy; // Update the target enemy for tracing
        canTrace = true;
        range = other.range; // Use the range from the other properties
        targetPriority = other.targetPriority; // Use the target priority from the other properties
    }
    
    return *this;
}

BulletProperties BulletProperties::operator+ (const BulletProperties& other) {
    BulletProperties result = *this;
    result += other; // Use the += operator to combine properties
    return result;
}

BulletProperties& BulletProperties::operator= (const BulletProperties& other) {
    if (this != &other) {
        canLead = other.canLead;
        canBlack = other.canBlack;
        canWhite = other.canWhite;
        canFrozen = other.canFrozen;
        canCamo = other.canCamo;
        canPurple = other.canPurple;
        canStripCamo = other.canStripCamo;
        canTrace = other.canTrace;
        targetEnemy = other.targetEnemy; 
        range = other.range; 
    }
    return *this;
}

BulletProperties& BulletProperties::getITracing(float range, TargetPriority targetPriority) {
    this->range = range;
    canTrace = true;
    targetEnemy.reset(); // Reset target enemy for tracing
    this->targetPriority = targetPriority; // Set the target priority for tracing
    return *this;
}

BulletProperties& BulletProperties::getITracing(std::shared_ptr<Enemy> enemy) {
    if (enemy) {
        targetEnemy = enemy;
        canTrace = true;
        range = 1000.0f; // Default range, can be adjusted as needed
    } else {
        canTrace = false;
        range = 0.0f;
    }
    return *this;
}

float BulletProperties::getRotation(float rotation, Vector2 position) {
    if (canTrace && !targetEnemy.expired()) {
        auto target = targetEnemy.lock();
        if (target) {
            Vector2 targetPosition = target->getPosition();
            float deltaX = targetPosition.x - position.x;
            float deltaY = targetPosition.y - position.y;
            return atan2f(deltaY, deltaX) * (180.0f / PI); // Convert radians to degrees
        }
    }
    return rotation; // Return the original rotation if tracing is not applicable
}