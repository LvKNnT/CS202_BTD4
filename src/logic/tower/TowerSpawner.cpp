#include "TowerSpawner.h"
#include <iostream>

// headers of towers
#include "towers/dartmonkey/DartMonkey.h"

TowerSpawner::TowerSpawner() {
    // Initialize tower templates
    init();
}

TowerSpawner::TowerSpawner(TowerModifies modifies)
    : currentModifies(modifies) {
    // Initialize tower templates
    init();
}

TowerSpawner::TowerSpawner(const TowerSpawner& other) {
    if (this != &other) {
        // Clear current tower templates
        towerTemplates.clear();

        // Deep copy of tower templates
        for (const auto& [type, tower] : other.towerTemplates) {
            towerTemplates[type] = tower->clone(); // Clone each tower template
        }
    } else {
        // should not be here
    }
}

TowerSpawner& TowerSpawner::operator=(const TowerSpawner& other) {
    if (this != &other) {
        // Clear current tower templates
        towerTemplates.clear();

        // Deep copy of tower templates
        for (const auto& [type, tower] : other.towerTemplates) {
            towerTemplates[type] = tower->clone(); // Clone each tower template
        }
    } else {
        // should not be here
    }
    return *this;
}

std::unique_ptr<TowerSpawner> TowerSpawner::clone() const {
    return std::make_unique<TowerSpawner>(*this);
}

void TowerSpawner::init() {
    // Initialize tower templates
    towerTemplates[TowerType::DartMonkey] = std::make_unique<DartMonkey>();
};  

void TowerSpawner::init(TowerModifies modifies) {
    // Initialize tower templates with modifies
    towerTemplates[TowerType::DartMonkey] = std::make_unique<DartMonkey>();
    towerTemplates[TowerType::DartMonkey]->setModifies(modifies); // Set modifies for the Dart Monkey tower
};

std::unique_ptr<Tower> TowerSpawner::getTower(TowerType type, Vector2 position, int towerID, const TowerModifies& modifies) {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        it->second->loadTexture(); // Load the texture for the tower

        // Create a new tower instance using the template
        std::unique_ptr<Tower> tower = it->second->clone();
        tower->position = position; // Set the position of the tower
        tower->towerId = towerID; // Set the tower ID

        for(auto& attack : tower->attacks) {
            attack->towerId = towerID; // Set the tower ID for each attack
            attack->position = position; // Set the position for each attack
        }
        tower->setModifies(modifies); // Set the modifies for the tower

        return tower;
    } else {
        // should not be here
        std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
        return nullptr; // Return nullptr if the type is not found
    }
}

int TowerSpawner::getRangeTower(TowerType type) const {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        int range = 0;
        for (const auto& attack : it->second->attacks) {
            if (attack) {
                range = std::max(range, static_cast<int>(attack->getRange()));
            }
        }
        return range; // Return the maximum range of the attacks
    } else {
        // should not be here
        std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
        return 0; // Return 0 if the type is not found
    }
}

LogicInfo TowerSpawner::getInfoTower(TowerType type, const TowerModifies& modifies) const {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        it->second->setModifies(modifies); 
        return it->second->getInfo(); // Return the info of the tower
    } else {
        // should not be here
        std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
    };

    return LogicInfo();
}

Rectangle TowerSpawner::getBoundingBox(TowerType type, Vector2 position) const {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        // Get the bounding box of the tower
        Rectangle boundingBox = it->second->getBoundingBox();
        
        // Since the default position is (0, 0), we need to adjust the bounding box position by using addition.
        boundingBox.x += position.x;
        boundingBox.y += position.y;

        return boundingBox; 
    } else {
        // should not be here
        std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
        return {0, 0, 0, 0}; // Return an empty rectangle if the type is not found
    }
}