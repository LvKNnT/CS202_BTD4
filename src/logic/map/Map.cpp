#include "Map.h"

Map::~Map() {
    
}

void Map::draw() const {
    DrawTextureEx(texture, {0, 0}, 0.0f, 1.0f, WHITE);
}

void Map::unLoad() {
    // Need to unload before closeWindow()
    UnloadImage(mapImage);
    UnloadTexture(texture);
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

Point::Type Map::getPointType(int index) const {
    if(index < 0 || index >= (int) enemyPath.size()) return Point::Type::None;
    return enemyPath[index].getType();
}

Vector2 Map::getCurrentPoint(int index) const {
    return enemyPath[index].position;
}

Vector2 Map::getNextPoint(int index) const {
    if(index + 1 >= (int) enemyPath.size()) return enemyPath.back().position;
    return enemyPath[index + 1].position;
}

bool Map::isLastPoint(int index) const {
    return index + 1 >= (int) enemyPath.size();
}

bool Map::isWithinBounds(Vector2 position) const {
    return position.x >= 0 && position.x < static_cast<float>(mapImage.width) &&
           position.y >= 0 && position.y < static_cast<float>(mapImage.height);
}