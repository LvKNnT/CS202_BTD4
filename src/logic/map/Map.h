#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <math.h>

#include "../../Properties.h"
#include "../../core/Game.h"
#include "Point.h"

class Map {
public:
    enum Type{
        Jungle,
        MonkeyLane
    };

private:
    Texture texture;
    std::vector<Point> enemyPath;
    Type type;
    Image mapImage;

public:
    Map(Type _type);
    ~Map();
    void draw() const;
    Point::Type getPointType(Vector2 position) const;
    Vector2 getCurrentPoint(int index) const;
    Vector2 getNextPoint(int index) const;
};

#endif // MAP_H