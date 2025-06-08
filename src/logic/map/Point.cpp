#include "Point.h"

Point::Type Point::getType() const {
    return type;
}

bool Point::canGetType(Vector2 curPoint, Point nextPoint) const {
    if(curPoint.x == nextPoint.position.x && curPoint.y == nextPoint.position.y) return 0;
    int kx = 1, ky = 1;
    if(position.x > nextPoint.position.x) kx = -1;
    if(position.y > nextPoint.position.y) ky = -1;

    if(position.x * kx <= curPoint.x * kx && curPoint.x * kx <= nextPoint.position.x * kx && position.y * ky <= curPoint.y * ky && curPoint.y * ky <= nextPoint.position.y * ky) return 1;
    return 0;
}
