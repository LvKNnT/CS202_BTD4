#include "MonkeyLane.h"
 
MonkeyLane::MonkeyLane() {
    MAXPATHS = 2;
    mapType = MapType::MonkeyLane; 

    // Generate the enemy path
    enemyPath[0].push_back(Point(-50, 400, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[0].push_back(Point(0, 390));
    enemyPath[0].push_back(Point(203, 390));
    enemyPath[0].push_back(Point(203, 275));
    enemyPath[0].push_back(Point(360, 275));
    enemyPath[0].push_back(Point(370, 655));
    enemyPath[0].push_back(Point(610, 660));
    enemyPath[0].push_back(Point(610, 635, Point::Type::Invisible));
    enemyPath[0].push_back(Point(605, 373));
    enemyPath[0].push_back(Point(590, 160));
    enemyPath[0].push_back(Point(200, 160));
    enemyPath[0].push_back(Point(205, 42));
    enemyPath[0].push_back(Point(725, 42));
    enemyPath[0].push_back(Point(735, 145));
    enemyPath[0].push_back(Point(875, 162));
    enemyPath[0].push_back(Point(875, 265));
    enemyPath[0].push_back(Point(730, 287));
    enemyPath[0].push_back(Point(730, 500));
    enemyPath[0].push_back(Point(497, 510, Point::Type::Invisible));
    enemyPath[0].push_back(Point(235, 510));
    enemyPath[0].push_back(Point(200, 510));
    enemyPath[0].push_back(Point(200, 820, Point::Type::Exit)); // player gets damage here

    enterEffects.push_back(Animation("movingTriangle", (Vector2) {70, 377}, 90.0f, 64, 40, 8, 0.25f));
    enterEffects.back().start();
}

std::unique_ptr<Map> MonkeyLane::clone() const {
    return std::make_unique<MonkeyLane>(*this);
}

Point::Type MonkeyLane::getPointType(Vector2 position) const {
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

void MonkeyLane::loadTexture()
{
    texture = Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb");
    mapImage = LoadImage("../assets/map/Monkey_lane_path_mask.png"); // MUST BE LOADED
    pathImage = LoadImage("../assets/map/Monkey_lane_thumb.png"); // Path image for collision detection
}

std::pair<Vector2, int> MonkeyLane::getPositionAndPathIdx(BloonType type) {
    return {getCurrentPoint(0, 0), 0}; // Default position and path index for this map
}