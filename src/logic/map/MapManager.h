#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "raylib.h"
#include <memory>

#include "Map.h"
#include "MapSpawner.h"

// This class manages the current map in the game
class MapManager {
    friend class LogicManager; // Allow LogicManager to access private members

public:
    MapManager();
    MapManager(const MapManager& other);
    ~MapManager() = default;

    MapManager& operator=(const MapManager& other);

    // Load a map by type
    void loadMap(MapType type);

    // Basic methods
    void drawMap() const;
    void updateMap();
    void unLoad();

    // save/load
    void save(std::string filePath) const;
    void load(std::string filePath);

    // Get the current map
    Map& getCurrentMap() const; // should be const
    MapType getMapType() const;
private:
    // Should be only one map at a time
    std::unique_ptr<MapSpawner> mapSpawner = std::make_unique<MapSpawner>(); // Factory to create maps based on type
    std::unique_ptr<Map> currentMap;
};

#endif // MAPMANAGER_H