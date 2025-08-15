#include "ReverseMonkeyLane.h"

ReverseMonkeyLane::ReverseMonkeyLane() {
    // Reverse path
    mapType = MapType::ReverseMonkeyLane;
    MAXPATHS = 1;
    enemyPath[0].push_back(Point(200, 770, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[0].push_back(Point(200, 510));
    enemyPath[0].push_back(Point(230, 510, Point::Type::Invisible));
    enemyPath[0].push_back(Point(497, 510));
    enemyPath[0].push_back(Point(730, 500));
    enemyPath[0].push_back(Point(730, 287));
    enemyPath[0].push_back(Point(875, 265));
    enemyPath[0].push_back(Point(875, 162));
    enemyPath[0].push_back(Point(735, 145));
    enemyPath[0].push_back(Point(725, 42));
    enemyPath[0].push_back(Point(205, 42));
    enemyPath[0].push_back(Point(200, 160));
    enemyPath[0].push_back(Point(590, 160));
    enemyPath[0].push_back(Point(605, 373, Point::Type::Invisible));
    enemyPath[0].push_back(Point(610, 635));
    enemyPath[0].push_back(Point(610, 660));
    enemyPath[0].push_back(Point(370, 655));
    enemyPath[0].push_back(Point(360, 275));
    enemyPath[0].push_back(Point(203, 275));
    enemyPath[0].push_back(Point(203, 390));
    enemyPath[0].push_back(Point(-100, 390, Point::Type::Exit));
    enterEffects.push_back(Animation("movingTriangle", (Vector2) {177, 700 - 40}, 0.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
}

std::unique_ptr<Map> ReverseMonkeyLane::clone() const {
    return std::make_unique<ReverseMonkeyLane>(*this);
}

Point::Type ReverseMonkeyLane::getPointType(Vector2 position) const {
    if(!Utils::isPositionInMap(position)) return Point::Type::None;
    int tolerance = 10;
    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));

    // check obstacle 
    Color obstacleColor = GetImageColor(mapImage, 610, 435); // 610 435 - an invisible point
    bool isObstacle = Utils::isColorDiffByTolerance(obstacleColor, pixelColor, tolerance);
    if(isObstacle) return Point::Type::Obstacle;

    // check for path
    Color pathColor = GetImageColor(mapImage, 203, 390); // 203 390 - an enemy path point
    bool isPath = Utils::isColorDiffByTolerance(pathColor, pixelColor, tolerance);
    if(isPath) return Point::Type::Enemy;

    return Point::Type::None; // can place tower here
}

void ReverseMonkeyLane::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb");
    mapImage = LoadImage("../assets/map/Monkey_lane_path_mask.png"); // MUST BE LOADED
    pathImage = LoadImage("../assets/map/Monkey_lane_thumb.png"); // Path image for collision detection
}

std::pair<Vector2, int> ReverseMonkeyLane::getPositionAndPathIdx(BloonType type) {
    return {getCurrentPoint(0, 0), 0}; // Default position and path index for this map
}