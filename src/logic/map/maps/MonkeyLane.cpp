#include "MonkeyLane.h"

MonkeyLane::MonkeyLane() {
    // Generate the enemy path
    enemyPath[0].push_back(Point(-50, 400, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath[0].push_back(Point(0, 390));
    enemyPath[0].push_back(Point(210, 390));
    enemyPath[0].push_back(Point(215, 290));
    enemyPath[0].push_back(Point(355, 285));
    enemyPath[0].push_back(Point(375, 655));
    enemyPath[0].push_back(Point(615, 660));
    enemyPath[0].push_back(Point(615, 600, Point::Type::Invisible));
    enemyPath[0].push_back(Point(615, 420));
    enemyPath[0].push_back(Point(590, 175));
    enemyPath[0].push_back(Point(215, 160));
    enemyPath[0].push_back(Point(215, 55));
    enemyPath[0].push_back(Point(725, 55));
    enemyPath[0].push_back(Point(745, 150));
    enemyPath[0].push_back(Point(890, 170));
    enemyPath[0].push_back(Point(890, 275));
    enemyPath[0].push_back(Point(750, 300));
    enemyPath[0].push_back(Point(740, 505));
    enemyPath[0].push_back(Point(480, 510, Point::Type::Invisible));
    enemyPath[0].push_back(Point(270, 510));
    enemyPath[0].push_back(Point(200, 510));
    enemyPath[0].push_back(Point(200, 760, Point::Type::Exit)); // player gets damage here
}

std::unique_ptr<Map> MonkeyLane::clone() const {
    return std::make_unique<MonkeyLane>(*this);
}

void MonkeyLane::loadTexture() {
    texture = Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb");
    mapImage = LoadImage("../assets/map/Monkey_lane_path_mask.png");
}

void MonkeyLane::update() {
    // This map has no dynamic elements to update
}

std::pair<Vector2, int> MonkeyLane::getPositionAndPathIdx(BloonType type) {
    return {getCurrentPoint(0, 0), 0}; // Default position and path index for this map
}