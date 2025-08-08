#ifndef CALTROPS_ATTACK_PATTERN_H
#define CALTROPS_ATTACK_PATTERN_H

#include "../AttackPattern.h"
#include <vector>

class CaltropsAttackPattern : public AttackPattern {
private:
    Vector2 position;
    const float range;
    std::vector<Vector2> caltropsPositions; 
    
public:
    CaltropsAttackPattern(MapManager* mapManager);
    CaltropsAttackPattern(MapManager* mapManager, Vector2 position, float range);
    ~CaltropsAttackPattern() override = default;

    std::unique_ptr<AttackPattern> clone() const override;

    void execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float& rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) override;
};

#endif // CALTROPS_ATTACK_PATTERN_H