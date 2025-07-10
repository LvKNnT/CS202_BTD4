#include "MapSpawner.h"

// headers of maps
#include "maps/MonkeyLane.h"

MapSpawner::MapSpawner() {
    /**
     * Technical issue:
     * Currently can't use constructor to initialize map templates
     * because the texture manager is not ready yet.
     */

    // Initialize map templates
    init();
}

MapSpawner::MapSpawner(const MapSpawner& other) {
    if (this != &other) {
        // Clear current map templates
        mapTemplates.clear();

        // deep copy of map templates
        for (const auto& [type, map] : other.mapTemplates) {
            mapTemplates[type] = map->clone(); // Clone each map template
        }
    } else {
        // should not be here
        std::cerr << "MapSpawner copy constructor called on self-assignment." << std::endl;
    }
}

MapSpawner& MapSpawner::operator=(const MapSpawner& other) {
    if (this != &other) {
        // Clear current map templates
        mapTemplates.clear();

        // deep copy of map templates
        for (const auto& [type, map] : other.mapTemplates) {
            mapTemplates[type] = map->clone(); // Clone each map template
        }
    } else {
        // should not be here
        std::cerr << "MapSpawner assignment operator called on self-assignment." << std::endl;
    }
    return *this;
}

std::unique_ptr<MapSpawner> MapSpawner::clone() const {
    return std::make_unique<MapSpawner>(*this);
}

// Initialize map templates
void MapSpawner::init() {
    mapTemplates[MapType::MonkeyLane] = std::make_unique<MonkeyLane>();
}

std::unique_ptr<Map> MapSpawner::getMap(MapType type) {
    auto it = mapTemplates.find(type);
    if (it != mapTemplates.end()) {
        it->second->loadTexture(); // Load the texture for the map

        return it->second->clone(); // Clone the map template
    }

    // should not be here
    std::cerr << "Map type not found: " << static_cast<int>(type) << std::endl;
    return nullptr;
}