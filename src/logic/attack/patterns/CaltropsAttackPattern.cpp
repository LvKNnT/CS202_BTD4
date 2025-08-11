#include "CaltropsAttackPattern.h"

#include "../../../utils/Utils.h"

CaltropsAttackPattern::CaltropsAttackPattern(MapManager* mapManager)
    : AttackPattern(mapManager), range(0.0f) {

    // Constructor implementation can be extended if needed
}

CaltropsAttackPattern::CaltropsAttackPattern(MapManager* mapManager, Vector2 position, float range)
    : AttackPattern(mapManager), position(position), range(range) {
    // Initialize the caltrops positions based on the given position and range
    caltropsPositions.clear();

    constexpr int ANGLE_STEPS = 360;
    constexpr float DEG_TO_RAD = 3.14159265f / 180.0f;

    // Precompute unit direction vectors for each angle
    static std::vector<Vector2> directions;
    if (directions.empty()) {
        directions.reserve(ANGLE_STEPS);
        for (int angle = 0; angle < ANGLE_STEPS; ++angle) {
            float rad = angle * DEG_TO_RAD;
            directions.push_back({std::cos(rad), std::sin(rad)});
        }
    }

    caltropsPositions.clear();
    caltropsPositions.reserve(ANGLE_STEPS);

    for (const Vector2& dir : directions) {
        Vector2 checkPos = position;

        // Step along the ray
        for (float dist = 0.0f; dist <= range; dist += 1.0f) {
            checkPos = position + dir * dist;

            if (mapManager->getCurrentMap().getEnemyPointType(checkPos) == Point::Type::Enemy) {
                caltropsPositions.push_back(checkPos);
                // break; // Found first enemy tile in this direction
            }
        }
    }

    std::cerr << "Caltrops positions initialized: " << caltropsPositions.size() << std::endl;
}

std::unique_ptr<AttackPattern> CaltropsAttackPattern::clone() const {
    return std::make_unique<CaltropsAttackPattern>(*this);
}

void CaltropsAttackPattern::execute(BulletManager& bulletManager, BulletType type, Vector2 position, Vector2 size, float& rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, BloonDebuff normalDebuff, BloonDebuff moabDebuff, AttackBuff& attackBuff, int towerId) {
    // Spawn a Caltrops bullet at the specified position

    int roll = Utils::rand(0, static_cast<int>(caltropsPositions.size()) - 1);
    Vector2 caltropPosition = caltropsPositions[roll - 1];

    rotation = atan2f(position.y - caltropPosition.y, position.x - caltropPosition.x);
    rotation = rotation * (180.0f / PI); 

    bulletManager.spawnBullet(type, caltropPosition, size, rotation, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff, attackBuff, towerId);
}