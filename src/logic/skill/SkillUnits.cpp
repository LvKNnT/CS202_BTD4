#include "SkillUnits.h"

TowerType& SkillFriendAccess::getTowerType(Tower& tower) {
    return tower.type; // Access the TowerType of the tower
}
Vector2& SkillFriendAccess::getTowerPosition(Tower& tower) {
    return tower.position; // Access the position of the tower
}
AttackBuff& SkillFriendAccess::getAttackBuff(Tower& tower) {
    return tower.attackBuff; // Access the AttackBuff of the tower
}

BloonDebuff& SkillFriendAccess::getDebuff(Enemy& enemy) {
    return enemy.debuff; // Access the BloonDebuff of the enemy
}

