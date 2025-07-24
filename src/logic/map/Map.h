#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <memory>
#include <math.h>
#include <vector>

#include "../../interfaces/Drawable.h"
#include "Point.h"
#include "MapUnits.h"
#include "../enemy/EnemyUnits.h"

class Map : public Drawable {
    friend class LogicManager; 

protected:
    Texture texture;
    static const int MAXPATHS = 2;
    std::vector<std::vector<Point> > enemyPath; // use vector<vector cause now we have 2 paths for jungle
    Image mapImage; 

public:
    Map();
    virtual std::unique_ptr<Map> clone() const = 0; 
    ~Map() = default; 

    // Basics settings
    virtual void loadTexture() = 0;
    void draw() const override;
    virtual void update() = 0;
    virtual std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) = 0; 
    void unLoad();

    // These functions should be the same for all maps
    Point::Type getPointType(Vector2 position) const; // For towers
    Point::Type getPointType(int index, int pathIdx = 0) const; // For enemies

    // only pass pathIdx when we are in jungle_lane
    Vector2 getCurrentPoint(int index, int pathIdx = 0) const;
    Vector2 getNextPoint(int index, int pathIdx = 0) const;
    bool isLastPoint(int index, int pathIdx = 0) const;

    bool isWithinBounds(Vector2 position) const;
};

#endif // MAP_H