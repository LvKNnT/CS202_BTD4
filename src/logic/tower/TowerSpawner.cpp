#include "TowerSpawner.h"
#include <iostream>

// headers of towers
#include "towers/dartmonkey/DartMonkey.h"

TowerSpawner::TowerSpawner() {
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

std::unique_ptr<Tower> TowerSpawner::getTower(TowerType type, Vector2 position, const TowerModifies& modifies) {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        it->second->loadTexture(); // Load the texture for the tower

        // Create a new tower instance using the template
        std::unique_ptr<Tower> tower = it->second->clone();
        tower->position = position; // Set the position of the tower
        for(auto& attack : tower->attacks) {
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