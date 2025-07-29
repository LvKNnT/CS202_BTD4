#ifndef POINT_H
#define POINT_H

#include "raylib.h"

class Point {
    friend class Map; // Allow Map to access private members
    friend class LogicManager; // Allow LogicManager to access private members

public:
    enum Type {
        None = 0,
        SpawnEnenmy,
        Exit,
        Invisible,
        Water, 
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
};

#endif // POINT_H