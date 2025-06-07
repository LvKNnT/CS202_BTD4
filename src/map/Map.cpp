#include "Map.h"

Map::Map(Type _type) : type(_type) {
    switch (type) {
        case MonkeyLane:
            texture = LoadTexture("assets/map/Monkey_lane_thumb.png");
            mapImage = LoadImage("assets/map/Monkey_lane_path_mask.png");
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
            break;
        
        case Jungle:
            break;
    }   
}

Map::~Map() {
    UnloadTexture(texture);
    UnloadImage(mapImage);
}

Texture Map::getTexture() const {
    return texture;
}

Point::Type Map::getPointType(Vector2 position) const {
    for(int i = 0; i < enemyPath.size() - 1; i++) {
        if(enemyPath[i].canGetType(position, enemyPath[i + 1])) return enemyPath[i].getType();
    }

    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));
    Color pathColor = GetImageColor(mapImage, static_cast<int>(enemyPath[1].position.x), static_cast<int>(enemyPath[1].position.y));
    int tolerance = 10;
    bool isPath = abs(pixelColor.r - pathColor.r) < tolerance && abs(pixelColor.g - pathColor.g) < tolerance && abs(pixelColor.b - pathColor.b) < tolerance;
    if(isPath) return Point::Type::Enemy;
    return Point::Type::None; // can place tower here
}

Vector2 Map::getCurrentPoint(int index) const {
    return enemyPath[index].position;
}

Vector2 Map::getNextPoint(int index) const {
    if(index + 1 >= (int) enemyPath.size()) return enemyPath.back().position; 
    return enemyPath[index + 1].position;
}
