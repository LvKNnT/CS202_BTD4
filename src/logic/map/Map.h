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
#include "../../utils/Utils.h"

class Map : public Drawable {
    friend class LogicManager; 
    friend class MapManager; 

protected:
    Texture texture;
    static const int MAXPATHS = 2;
    std::vector<std::vector<Point> > enemyPath; // use vector<vector cause now we have 2 paths for jungle
    Image mapImage;
    Image pathImage;
    MapType mapType;

public:
    Map();
    virtual std::unique_ptr<Map> clone() const = 0; 
    virtual ~Map() = default; 

    // Basics settings
    virtual void loadTexture() = 0;
    virtual void update() = 0;
    virtual std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) = 0; 
    void draw() const override;
    void unLoad();
    
    // Get the type of points
    float distanceToEndPoint(Vector2 position, int index, int pathIdx = 0) const; // For enemies
    virtual Point::Type getPointType(int index, int pathIdx = 0) const; // For enemies
    virtual Point::Type getTowerPointType(Vector2 position) const; // For Tower
    virtual Point::Type getEnemyPointType(Vector2 position) const; // For Tower
    
    // only pass pathIdx when we are in jungle_lane
    virtual Vector2 getCurrentPoint(int index, int pathIdx = 0) const;
    Vector2 getNextPoint(int index, int pathIdx = 0) const;
    Vector2 getPreviousPoint(int index, int pathIdx = 0) const;
    bool isLastPoint(int index, int pathIdx = 0) const;

    bool isWithinBounds(Vector2 position) const;
};

#endif // MAP_H