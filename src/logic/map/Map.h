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
#include "../../interfaces/Animation.h"
#include "../enemy/EnemyUnits.h"
#include "../../utils/Utils.h"

class Map : public Drawable {
    friend class LogicManager; 
    friend class MapManager; 

protected:
    int MAXPATHS;
    Texture texture;
    std::vector<Point> enemyPath[2]; // use vector<vector cause now we have 2 paths for jungle
    std::vector<Animation> enterEffects;
    Image mapImage;
    Image pathImage;
    MapType mapType;

public:
    Map();
    virtual std::unique_ptr<Map> clone() const = 0; 
    virtual ~Map() = default; 

    // Basics settings
    virtual void loadTexture() = 0;
    virtual void update();
    virtual std::pair<Vector2, int> getPositionAndPathIdx(BloonType type) = 0; 
    void draw() const override;
    void unLoad();
    
    // Get the type of points
    float getTotalDistance(int pathIdx = 0) const; // For enemies
    float distanceToEndPoint(Vector2 position, int index, int pathIdx = 0) const; // For enemies
    virtual Point::Type getPointType(int index, int pathIdx = 0) const; // For enemies
    virtual Point::Type getPointType(Vector2 position) const; // For Tower
    
    // only pass pathIdx when we are in jungle_lane
    virtual Vector2 getCurrentPoint(int index, int pathIdx = 0) const;
    Vector2 getNextPoint(int index, int pathIdx = 0) const;
    Vector2 getPreviousPoint(int index, int pathIdx = 0) const;
    bool isLastPoint(int index, int pathIdx = 0) const;

    bool isWithinBounds(Vector2 position) const;
};

#endif // MAP_H