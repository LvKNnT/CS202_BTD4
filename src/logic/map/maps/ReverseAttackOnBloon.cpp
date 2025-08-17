#include "ReverseAttackOnBloon.h"

ReverseAttackOnBloon::ReverseAttackOnBloon(){
    mapType = MapType::ReverseAttackOnBloon; 
    MAXPATHS = 1;
    // path 0
    enemyPath[0].push_back(Point(1050, 578, Point::Type::SpawnEnenmy)); // now spawn here
    enemyPath[0].push_back(Point(883, 628));
    enemyPath[0].push_back(Point(631, 598));
    enemyPath[0].push_back(Point(636, 595));
    enemyPath[0].push_back(Point(650, 423));
    enemyPath[0].push_back(Point(727, 353));
    enemyPath[0].push_back(Point(920, 336));
    enemyPath[0].push_back(Point(939, 303));
    enemyPath[0].push_back(Point(922, 257));
    enemyPath[0].push_back(Point(887, 190));
    enemyPath[0].push_back(Point(638, 200));
    enemyPath[0].push_back(Point(638, 624));
    enemyPath[0].push_back(Point(583, 680));
    enemyPath[0].push_back(Point(408, 680));
    enemyPath[0].push_back(Point(339, 614));
    enemyPath[0].push_back(Point(339, -100, Point::Type::Exit)); // player gets damage here
    enterEffects.push_back(Animation("movingTriangle", (Vector2) {930, 610}, -90.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
}

std::unique_ptr<Map> ReverseAttackOnBloon::clone() const {
    return std::make_unique<ReverseAttackOnBloon>(*this);
}

Point::Type ReverseAttackOnBloon::getPointType(Vector2 position) const {
    if(!Utils::isPositionInMap(position)) return Point::Type::None;
    int tolerance = 10;
    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));

    // check obstacle 558, 508
    Color obstacleColor = GetImageColor(mapImage, 558, 508);  
    bool isObstacle = Utils::isColorDiffByTolerance(obstacleColor, pixelColor, tolerance);
    if(isObstacle) return Point::Type::Obstacle;

    return Point::Type::None; // can place tower here
}

void ReverseAttackOnBloon::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("AttackOnBloonThumb");
    mapImage = LoadImage("../assets/map/Attack_on_bloon_path_mask.png"); // MUST BE LOADED
}

std::pair<Vector2, int> ReverseAttackOnBloon::getPositionAndPathIdx(BloonType type) {
    pathIdxCount = (pathIdxCount + 1) % MAXPATHS;
    return {getCurrentPoint(0, pathIdxCount), pathIdxCount}; // Default position and path index for this map
}
