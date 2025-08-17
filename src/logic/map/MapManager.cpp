#include "MapManager.h"
#include <fstream>

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

Map& MapManager::getCurrentMap() const {
    if(!currentMap) {
        // should not be here
        std::cerr << "Current map is not loaded. Please load a map before accessing it." << std::endl;
    }

    return *currentMap; 
}

MapType MapManager::getMapType() const {
    if(!currentMap) {
        // should not be here
        std::cerr << "Current map is not loaded. Please load a map before accessing its type." << std::endl;
        return MapType::MonkeyLane; // Default to Jungle if no map is loaded
    }

    return currentMap->mapType; 
}

void MapManager::save(std::string filePath, bool isReverse) const {
    if(!currentMap) {
        // should not be here
        std::cerr << "Current map is not loaded. Please load a map before saving." << std::endl;
        return;
    }

    std::fstream file(filePath, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for saving map." << std::endl;
        return;
    }

    // file << "map\n";
    file << static_cast<int>(currentMap->mapType) << std::endl;
    file.close();
}

void MapManager::load(std::string filePath) {
    std::fstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for loading map." << std::endl;
        return;    
    } 

    int mapTypeInt;
    file >> mapTypeInt; 
    std::cerr << "Loading map type: " << mapTypeInt << std::endl;
    MapType mapType = static_cast<MapType>(mapTypeInt);

    loadMap(mapType);

    file.close();
}