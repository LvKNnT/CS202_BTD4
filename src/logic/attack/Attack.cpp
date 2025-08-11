#include "Attack.h"

Attack::Attack(float range, float cooldown, Vector2 position, int towerId, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff)
    : range(range), cooldown(cooldown), timer(0.0f), position(position), towerId(towerId), damage(damage), speed(speed), pierce(pierce), lifeSpan(lifeSpan), properties(properties), normalDebuff(normalDebuff), moabDebuff(moabDebuff) {
    // Constructor implementation can be extended if needed
}

Attack::Attack(const Attack& other)
    : range(other.range), cooldown(other.cooldown), timer(other.timer), position(other.position), towerId(other.towerId),
      damage(other.damage), speed(other.speed), pierce(other.pierce), lifeSpan(other.lifeSpan),
      properties(other.properties), normalDebuff(other.normalDebuff), moabDebuff(other.moabDebuff), tag(other.tag) {
    if (other.attackPattern) {
        attackPattern = other.attackPattern->clone();
    }
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

Vector2 Attack::getPosition() const {
    return position;
}
std::string Attack::getTag() const {
    return tag;
}
BulletProperties& Attack::getProperties() {
    return properties;
}
BloonDebuff& Attack::getNormalDebuff() {
    return normalDebuff;
}
BloonDebuff& Attack::getMoabDebuff() {
    return moabDebuff;
}
void Attack::setAttackPattern(std::unique_ptr<AttackPattern> newAttackPattern) {
    attackPattern = std::move(newAttackPattern);
}
std::unique_ptr<AttackPattern>& Attack::getAttackPattern() {
    return attackPattern;
}
bool Attack::isRotateTower() const {
    return true; // Default implementation assumes rotation is needed
}
float Attack::getRotateTower(float rotation) {
    return rotation; // no change
}
int Attack::getTowerId() const {
    return towerId;
}