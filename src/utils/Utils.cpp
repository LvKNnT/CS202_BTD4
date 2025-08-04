#include "Utils.h"

bool Utils::isMouseInMap() {
    Vector2 mousePos = GetMousePosition();
    return 0 < mousePos.x && mousePos.x < Properties::mapWidth && 0 < mousePos.y && mousePos.y < Properties::mapHeight;
}

bool Utils::isPositionInMap(Vector2 position) {
    return 0 < position.x && position.x < Properties::mapWidth && 0 < position.y && position.y < Properties::mapHeight;
}

bool Utils::isColorDiffByTolerance(Color a, Color b, float tolerance) {
    return abs(a.r - b.r) < tolerance && abs(a.g - b.g) < tolerance && abs(a.b - b.b) < tolerance;
}
