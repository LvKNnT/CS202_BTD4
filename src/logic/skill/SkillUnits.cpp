#include "SkillUnits.h"

Vector2& SkillFriendAccess::getTowerPosition(Tower& tower) {
    return tower.position; // Access the position of the tower
}
float& SkillFriendAccess::getTowerRotation(Tower& tower) {
    return tower.rotation; // Access the rotation of the tower
}
TowerType& SkillFriendAccess::getTowerType(Tower& tower) {
    return tower.type; // Access the TowerType of the tower
}
TargetPriority& SkillFriendAccess::getTargetPriority(Tower& tower) {
    return tower.targetPriority; // Access the TargetPriority of the tower
}
AttackBuff& SkillFriendAccess::getAttackBuff(Tower& tower) {
    return tower.attackBuff; // Access the AttackBuff of the tower
}
std::string& SkillFriendAccess::getTag(Tower& tower) {
    return tower.tag; // Access the tag of the tower
}
int& SkillFriendAccess::getTowerId(Tower& tower) {
    return tower.towerId; // Access the tower ID
}

Vector2& SkillFriendAccess::getEnemyPosition(Enemy& enemy) {
    return enemy.position; // Access the position of the enemy
}
BloonDebuff& SkillFriendAccess::getDebuff(Enemy& enemy) {
    return enemy.debuff; // Access the BloonDebuff of the enemy
}
BloonType& SkillFriendAccess::getType(Enemy& enemy) {
    return enemy.type; // Access the BloonType of the enemy
}
int& SkillFriendAccess::getLivesLost(Enemy& enemy) {
    return enemy.livesLost; // Access the lives lost by the enemy
}

BloonType &SkillFriendAccess::getEnemyType(Enemy &enemy) {
    return enemy.type;
}

int &SkillFriendAccess::getEnemyHealth(Enemy &enemy) {
    return enemy.health;
}

int& SkillFriendAccess::getTrackIndex(Enemy& enemy) {
    return enemy.trackIndex; // Access the track index of the enemy
}
int& SkillFriendAccess::getPathIndex(Enemy& enemy) {
    return enemy.pathIndex; // Access the path index of the enemy
}