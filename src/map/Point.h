#ifndef POINT_H
#define POINT_H

#include "raylib.h"

class Point {
public:
    enum Type {
        None = 0,
        SpawnEnenmy,
        Exit,
        Invisible,
        Enemy
    };

private:
    Vector2 position;
    Type type;

public:
    Point(float x, float y, Type _type = Type::Enemy) 
        : position{ x, y }, type(_type) {}

    Type getType() const;
    bool canGetType(Vector2 curPoint, Point nextPoint) const;
    friend class Map;
};

#endif // POINT_H