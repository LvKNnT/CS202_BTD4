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

protected:
    Texture texture;
    static const int MAXPATHS = 2;
    std::vector<Point> enemyPath[MAXPATHS]; // use vector<vector cause now we have 2 paths for jungle
    Type type;
    Image mapImage; 

public:
    //Map(Type _type);
    ~Map(); 
    void draw() const;
    Point::Type getPointType(Vector2 position) const;
    // only pass pathIdx when we are in jungle_lane
    Vector2 getCurrentPoint(int index, int pathIdx = 0) const;
    Vector2 getNextPoint(int index, int pathIdx = 0) const;
};

class MonkeyLane: public Map {
public:
    MonkeyLane();
};

class Jungle: public Map {
public:
    Jungle();
};

#endif // MAP_H