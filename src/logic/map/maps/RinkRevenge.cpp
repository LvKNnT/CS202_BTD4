#include "RinkRevenge.h"

RinkRevenge::RinkRevenge() : pathIdxCount(0) {
    mapType = MapType::RinkRevenge; 
    MAXPATHS = 2;
    // path 0
    enemyPath[0].push_back(Point(339, -50, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[0].push_back(Point(339, 614)); 
    enemyPath[0].push_back(Point(408, 680)); 
    enemyPath[0].push_back(Point(583, 680)); 
    enemyPath[0].push_back(Point(638, 624)); 
    enemyPath[0].push_back(Point(639, -50, Point::Type::Exit)); // player gets damage here
    enterEffects.push_back(Animation("movingTriangle", (Vector2) {355, 70}, 180.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
    
    // path 1
    enemyPath[1].push_back(Point(-50, 260, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[1].push_back(Point(815, 247)); 
    enemyPath[1].push_back(Point(855, 262)); 
    enemyPath[1].push_back(Point(875, 283)); 
    enemyPath[1].push_back(Point(901, 328)); 
    enemyPath[1].push_back(Point(906, 383)); 
    enemyPath[1].push_back(Point(898, 434)); 
    enemyPath[1].push_back(Point(880, 460)); 
    enemyPath[1].push_back(Point(855, 483)); 
    enemyPath[1].push_back(Point(804, 487)); 
    enemyPath[1].push_back(Point(-50, 510, Point::Type::Exit)); // player gets damage here
    enterEffects.push_back(Animation("movingTriangle", (Vector2) {70, 240}, 90.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
}

std::unique_ptr<Map> RinkRevenge::clone() const {
    return std::make_unique<RinkRevenge>(*this);
}

Point::Type RinkRevenge::getPointType(Vector2 position) const {
    if(!Utils::isPositionInMap(position)) return Point::Type::None;
    int tolerance = 10;
    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));

    // check Water 750 130
    Color waterColor = GetImageColor(mapImage, 750, 130);  
    bool isWater = Utils::isColorDiffByTolerance(waterColor, pixelColor, tolerance);
    if(isWater) return Point::Type::Water;

    // check obstacle 940, 629
    Color obstacleColor = GetImageColor(mapImage, 940, 629);  
    bool isObstacle = Utils::isColorDiffByTolerance(obstacleColor, pixelColor, tolerance);
    if(isObstacle) return Point::Type::Obstacle;

    // check for path
    Color pathColor = GetImageColor(mapImage, 339, 614); // 339 614 - an enemy path point
    bool isPath = Utils::isColorDiffByTolerance(pathColor, pixelColor, tolerance);
    if(isPath) return Point::Type::Enemy;

    return Point::Type::None; // can place tower here
}

void RinkRevenge::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("RinkRevengeThumb");
    mapImage = LoadImage("../assets/map/Rink_revenge_path_mask.png"); // MUST BE LOADED
}

std::pair<Vector2, int> RinkRevenge::getPositionAndPathIdx(BloonType type) {
    pathIdxCount = (pathIdxCount + 1) % MAXPATHS;
    return {getCurrentPoint(0, pathIdxCount), pathIdxCount}; // Default position and path index for this map
}
