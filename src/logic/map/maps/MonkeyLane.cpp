#include "MonkeyLane.h"
 
MonkeyLane::MonkeyLane() {
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
    enemyPath[0].push_back(Point(200, 695, Point::Type::Exit)); // player gets damage here
}

std::unique_ptr<Map> MonkeyLane::clone() const {
    return std::make_unique<MonkeyLane>(*this);
}

void MonkeyLane::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb");
    mapImage = LoadImage("../assets/map/Monkey_lane_path_mask.png");
    //pixelColors = std::shared_ptr<Color[]>(LoadImageColors(mapImage)); // create a new pixel colors array
}

void MonkeyLane::update() {
    // This map has no dynamic elements to update
}

std::pair<Vector2, int> MonkeyLane::getPositionAndPathIdx(BloonType type) {
    return {getCurrentPoint(0, 0), 0}; // Default position and path index for this map
}