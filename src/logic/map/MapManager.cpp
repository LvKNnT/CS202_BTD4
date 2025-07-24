#include "MapManager.h"
// #include "maps/MonkeyLane.h"

MapManager::MapManager() {
    // Initialize unique_ptr
    mapSpawner = std::make_unique<MapSpawner>();
    currentMap = nullptr;
}

MapManager::MapManager(const MapManager& other) {
    if (this != &other) {
        mapSpawner = other.mapSpawner->clone();
        
        if(other.currentMap) {
            currentMap = other.currentMap->clone(); // Clone the current map
        } else {
            currentMap = nullptr; // If the other map is null, set this to null
        }
    }
    else {
        // should not be here
    }
}

MapManager& MapManager::operator=(const MapManager& other) {
    if (this != &other) {
        mapSpawner = other.mapSpawner->clone(); // Clone the map spawner
        
        if(other.currentMap) {
            currentMap = other.currentMap->clone(); // Clone the current map
        } else {
            currentMap = nullptr; // If the other map is null, set this to null
        }
    } else {
        // should not be here
    }
    return *this;
}

void MapManager::loadMap(MapType type) {
    // only one map available now so bruh
    currentMap = mapSpawner->getMap(type);
}

void MapManager::drawMap() const {
    if(!currentMap) {
        // should not be here
        std::cerr << "Current map is not loaded. Please load a map before accessing it." << std::endl;
    }

    currentMap->draw();
}

void MapManager::updateMap() {
    if(!currentMap) {
        // should not be here
        std::cerr << "Current map is not loaded. Please load a map before accessing it." << std::endl;
    }

    currentMap->update();
}

void MapManager::unLoad() {
    if(currentMap) {
        currentMap->unLoad(); // Unload the current map resources
    }
}

Map& MapManager::getCurrentMap() {
    if(!currentMap) {
        // should not be here
        std::cerr << "Current map is not loaded. Please load a map before accessing it." << std::endl;
    }

    return *currentMap; 
}