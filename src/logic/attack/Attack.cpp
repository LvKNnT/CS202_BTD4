#include "Attack.h"

Attack::Attack(float range, float cooldown, Vector2 position, int damage, int speed, int pierce, float lifeSpan)
    : range(range), cooldown(cooldown), timer(0.0f), position(position), damage(damage), speed(speed), pierce(pierce), lifeSpan(lifeSpan) {
    // Constructor implementation can be extended if needed
}

float Attack::getRange() const {
    return range;
}
void Attack::setRange(float newRange) {
    range = newRange;
}

float Attack::getCooldown() const {
    return cooldown;
}
void Attack::setCooldown(float newCooldown) {
    cooldown = newCooldown;
}

int Attack::getDamage() const {
    return damage;
}
void Attack::setDamage(int newDamage) {
    damage = newDamage;
}

int Attack::getSpeed() const {
    return speed;
}
void Attack::setSpeed(int newSpeed) {
    speed = newSpeed;
}

int Attack::getPierce() const {
    return pierce;
}
void Attack::setPierce(int newPierce) {
    pierce = newPierce;
}

float Attack::getLifeSpan() const {
    return lifeSpan;
}
void Attack::setLifeSpan(float newLifeSpan) {
    lifeSpan = newLifeSpan;
}