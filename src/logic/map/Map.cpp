#include "Map.h"
#include "../../core/Game.h"
#include "raymath.h"

Map::Map() 
    : enemyPath(MAXPATHS) { 

}

void Map::draw() const {
    DrawTextureEx(texture, {0, 0}, 0.0f, 1.0f, WHITE);

    // Purely for testing hitbox
    // const float width = 50.0f;
    // for(const auto& path : enemyPath) {
    //     for(const auto& point : path) {
    //         // Draw a square size 5.0f centered at each point
    //         Vector2 topLeft = { point.position.x - width / 2, point.position.y - width / 2};
    //         DrawRectangleV(topLeft, {width, width}, (Color) {0, 255, 0, 128}); // Draw the point in green with some transparency
    //     }
    // }
}

void Map::unLoad() {
    // Need to unload before closeWindow()
    UnloadImage(mapImage);
}

Point::Type Map::getTowerPointType(Vector2 position) const {
    if(!Utils::isPositionInMap(position)) return Point::Type::None;
    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));
    Color pathColor = GetImageColor(mapImage, static_cast<int>(enemyPath[0][1].position.x), static_cast<int>(enemyPath[0][1].position.y));
    //Color pathColor = GetImageColor(pathImage, static_cast<int>(position.x), static_cast<int>(position.y));
    int tolerance = 10;
    bool isPath = Utils::isColorDiffByTolerance(pathColor, pixelColor, tolerance);
    if(isPath) return Point::Type::Enemy;

    return Point::Type::None; // can place tower here
}

Point::Type Map::getEnemyPointType(Vector2 position) const {
    if(!Utils::isPositionInMap(position)) return Point::Type::None;
    Color pixelColor = GetImageColor(mapImage, static_cast<int>(position.x), static_cast<int>(position.y));
    Color pathColor = GetImageColor(mapImage, static_cast<int>(enemyPath[0][1].position.x), static_cast<int>(enemyPath[0][1].position.y));
    //Color pathColor = GetImageColor(pathImage, static_cast<int>(position.x), static_cast<int>(position.y));
    int tolerance = 10;
    bool isPath = Utils::isColorDiffByTolerance(pathColor, pixelColor, tolerance);
    if(isPath) return Point::Type::Enemy;

    return Point::Type::None; // can place tower here
}

Point::Type Map::getPointType(int index, int pathIdx) const {
    if(index < 0 || index >= (int) enemyPath[pathIdx].size()) return Point::Type::None;
    return enemyPath[pathIdx][index].getType();
}

float Map::distanceToEndPoint(Vector2 position, int index, int pathIdx) const {
    float distance = 0.0f;

    Vector2 currentPoint = getCurrentPoint(index, pathIdx);
    distance += Vector2Distance(position, currentPoint);
    
    for(int i = index; i < (int) enemyPath[pathIdx].size(); ++i) {
        Vector2 nextPoint = getNextPoint(i, pathIdx);
        distance += Vector2Distance(currentPoint, nextPoint);
        currentPoint = nextPoint;
    }

    return distance;
}

Vector2 Map::getCurrentPoint(int index, int pathIdx) const {
    return enemyPath[pathIdx][index].position;
}

Vector2 Map::getNextPoint(int index, int pathIdx) const {
    if(index + 1 >= (int) enemyPath[pathIdx].size()) return enemyPath[pathIdx].back().position; 
    return enemyPath[pathIdx][index + 1].position;
}

Vector2 Map::getPreviousPoint(int index, int pathIdx) const {
    if(index - 1 < 0) return enemyPath[pathIdx][0].position;
    return enemyPath[pathIdx][index - 1].position;
}

bool Map::isLastPoint(int index, int pathIdx) const {
    return index + 1 >= (int) enemyPath[pathIdx].size();
}

bool Map::isWithinBounds(Vector2 position) const {
    return position.x >= 0 && position.x < static_cast<float>(mapImage.width) &&
           position.y >= 0 && position.y < static_cast<float>(mapImage.height);
}

