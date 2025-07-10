#include "MonkeyLane.h"

MonkeyLane::MonkeyLane() {
    // Generate the enemy path
    enemyPath.push_back(Point(-50, 400, Point::Type::SpawnEnenmy)); // enemy goes from there
    enemyPath.push_back(Point(0, 390));
    enemyPath.push_back(Point(210, 390));
    enemyPath.push_back(Point(215, 290));
    enemyPath.push_back(Point(355, 285));
    enemyPath.push_back(Point(375, 655));
    enemyPath.push_back(Point(615, 660));
    enemyPath.push_back(Point(615, 600, Point::Type::Invisible));
    enemyPath.push_back(Point(615, 420));
    enemyPath.push_back(Point(590, 175));
    enemyPath.push_back(Point(215, 160));
    enemyPath.push_back(Point(215, 55));
    enemyPath.push_back(Point(725, 55));
    enemyPath.push_back(Point(745, 150));
    enemyPath.push_back(Point(890, 170));
    enemyPath.push_back(Point(890, 275));
    enemyPath.push_back(Point(750, 300));
    enemyPath.push_back(Point(740, 505));
    enemyPath.push_back(Point(480, 510, Point::Type::Invisible));
    enemyPath.push_back(Point(270, 510));
    enemyPath.push_back(Point(210, 760, Point::Type::Exit)); // player gets damage here
}

std::unique_ptr<Map> MonkeyLane::clone() const {
    return std::make_unique<MonkeyLane>(*this);
}

void MonkeyLane::loadTexture() {
    Game::Instance().getTextureManager().loadTexture("MonkeyLaneThumb", "assets/map/Monkey_lane_thumb.png");
    texture = Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb");
    mapImage = LoadImage("assets/map/Monkey_lane_path_mask.png");
}

void MonkeyLane::update() {
    // This map has no dynamic elements to update
}