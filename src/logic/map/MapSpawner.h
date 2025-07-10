#ifndef MAPSPAWNER_H
#define MAPSPAWNER_H

#include "Map.h"
#include <map>

// We use design pattern Factory Method Pattern to create maps

class MapSpawner {
private:
    struct MapTypeCompare {
        bool operator()(const MapType& a, const MapType& b) const {
            return static_cast<int>(a) < static_cast<int>(b);
        }
    };
    std::map<MapType, std::unique_ptr<Map>, MapTypeCompare> mapTemplates;

public:
    MapSpawner();
    MapSpawner(const MapSpawner& other);
    ~MapSpawner() = default;

    MapSpawner& operator=(const MapSpawner& other);
    std::unique_ptr<MapSpawner> clone() const;

    void init();

    // Returns a unique_ptr to a new Map of the given type
    std::unique_ptr<Map> getMap(MapType type);
};

#endif // MAPSPAWNER_H