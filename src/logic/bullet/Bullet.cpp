#include "Bullet.h"

Bullet::Bullet(BulletType type)
    : type(type) {
    // Constructor implementation can be extended if needed
}

int Bullet::getDamage(BloonType type, bool isCamo) {
    int damage = this->damage;

    if(isCamo) damage += normalDebuff.bonusCamoDamage;
    if(type == BloonType::Lead || type == BloonType::Ddt) damage += normalDebuff.bonusLeadDamage;

    if(type < BloonType::Moab) return damage + normalDebuff.bonusDamage; 

    return damage + moabDebuff.bonusDamage; // moab class
}