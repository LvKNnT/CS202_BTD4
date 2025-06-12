#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <math.h>

#include "../../core/Game.h"
#include "../../interfaces/Drawable.h"
#include "Point.h"

class Map : public Drawable {
public:
    enum Type{
        Jungle,
        MonkeyLane
    };

private:
    std::vector<Point> enemyPath;
    Type type;
    Image mapImage;
    Texture texture;

public:
    Map(Type _type);
    ~Map();

    void draw() const override;

    Point::Type getPointType(Vector2 position) const; // For towers
    Point::Type getPointType(int index) const; // For enemies

    Vector2 getCurrentPoint(int index) const;
    Vector2 getNextPoint(int index) const;
    bool isLastPoint(int index) const;
};

#endif // MAP_H