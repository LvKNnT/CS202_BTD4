#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <memory>
#include <math.h>

#include "../../interfaces/Drawable.h"
#include "Point.h"
#include "MapUnits.h"

class Map : public Drawable {
    friend class LogicManager; 

protected:
    std::vector<Point> enemyPath;
    Image mapImage;
    Texture texture;

public:
    Map() = default;
    virtual std::unique_ptr<Map> clone() const = 0; 
    virtual ~Map();

    // Basics settings
    virtual void loadTexture() = 0;
    void draw() const override;
    virtual void update() = 0;
    void unLoad();
    
    // These functions should be the same for all maps
    Point::Type getPointType(Vector2 position) const; // For towers
    Point::Type getPointType(int index) const; // For enemies

    Vector2 getCurrentPoint(int index) const;
    Vector2 getNextPoint(int index) const;
    bool isLastPoint(int index) const;

    bool isWithinBounds(Vector2 position) const;
};

#endif // MAP_H