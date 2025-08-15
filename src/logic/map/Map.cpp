#include "Map.h"
#include "../../core/Game.h"
#include "raymath.h"

Map::Map() { 

}

void Map::draw() const {
    DrawTextureEx(texture, {0, 0}, 0.0f, 1.0f, WHITE);
    for(auto &animation:enterEffects) {
        animation.draw();
    }
}

void Map::update() {
    for(auto &animation:enterEffects) {
        animation.update();
    }
}

void Map::unLoad() {
    // Need to unload before closeWindow()
    UnloadImage(mapImage);
}

Point::Type Map::getPointType(Vector2 position) const {
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

float Map::getTotalDistance(int pathIdx) const {
    float totalDistance = 0.0f;
    for(int i = 0; i + 1 < (int) enemyPath[pathIdx].size(); ++i) {
        totalDistance += Vector2Distance(enemyPath[pathIdx][i].position, enemyPath[pathIdx][i + 1].position);
    }
    return totalDistance;
}

float Map::distanceToEndPoint(Vector2 position, int index, int pathIdx) const {
    float distance = 0.0f;

    Vector2 currentPoint = getNextPoint(index, pathIdx);
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

