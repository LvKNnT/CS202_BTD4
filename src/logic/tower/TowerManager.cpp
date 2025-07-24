#include "TowerManager.h"
#include <filesystem>
#include <iostream>

TowerManager::TowerManager(TowerModifies modifies)
    : currentModifies(modifies), towerIDCounter(0) {
    // Initialize unique_ptr
    towerSpawner = std::make_unique<TowerSpawner>(currentModifies);
}

TowerManager::TowerManager(const TowerManager& other) {
    if (this != &other) {
        currentModifies = other.currentModifies; // Copy the current modifies
        towerSpawner = other.towerSpawner->clone();
        towerIDCounter = other.towerIDCounter; // Copy the tower ID counter

        towerList.clear();
        for (const auto& tower : other.towerList) {
            towerList.push_back(tower->clone());
        }
    }
    else {
        // should not be here
        std::cerr << "Error: Attempted to copy TowerManager to itself." << std::endl;
    }
}

TowerManager& TowerManager::operator=(const TowerManager& other) {
    if (this != &other) {
        currentModifies = other.currentModifies; 
        towerSpawner = other.towerSpawner->clone();
        towerIDCounter = other.towerIDCounter; // Copy the tower ID counter

        towerList.clear();
        for (const auto& tower : other.towerList) {
            towerList.push_back(tower->clone());
        }
    }
    else {
        // should not be here
        std::cerr << "Error: Attempted to assign TowerManager to itself." << std::endl;
    }  
    return *this;
}

void TowerManager::spawnTower(TowerType type, Vector2 position) {
    std::unique_ptr<Tower> tower = towerSpawner->getTower(type, position, towerIDCounter++, currentModifies);

    if (tower) {
        towerList.push_back(std::move(tower));
    } else {
        std::cerr << "Failed to spawn tower of type: " << static_cast<int>(type) << std::endl;
    }
}

LogicInfo TowerManager::getInfoTower(TowerType type) const {
    return towerSpawner->getInfoTower(type, currentModifies);
}

LogicInfo TowerManager::getInfoTower(Vector2 position) const {
    Tower* tower = getTowerFromPosition(position);
    if (tower) {
        return tower->getInfo();
    }

    // should be here only if no tower is found at the position
    std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    return LogicInfo(); // Return an empty LogicInfo if no tower is found
}

void TowerManager::drawTowers() const {
    for (const auto& tower : towerList) {
        if (tower) {
            tower->draw();
        } else {
            std::cerr << "Tower is null." << std::endl;
        }
    }
}

void TowerManager::updateTowers() {
    for (const auto& tower : towerList) {
        if (tower && tower->isActive()) {
            tower->update();
        } else {
            std::cerr << "Tower is null or inactive." << std::endl;
        }
    }
}

void TowerManager::unLoad() {
    for (auto& tower : towerList) {
        if (tower) {
            tower->unLoad();
        } else {
            std::cerr << "Tower is null during unload." << std::endl;
        }
    }
    towerList.clear(); // Clear the tower list after unloading
}

Tower* TowerManager::getTowerFromPosition(Vector2 position) const {
    for (const auto& tower : towerList) {
        if (tower && CheckCollisionPointRec(position, tower->getBoundingBox())) {
            return tower.get(); // Return the tower if the position collides with its bounding box
        }
    }
    return nullptr; // No tower found at the given position
}

void TowerManager::chooseNextPriority(Vector2 position) {
    Tower* tower = getTowerFromPosition(position);
    if (tower) {
        tower->targetPriority = static_cast<TargetPriority>((static_cast<int>(tower->targetPriority) + 1) % 4);
    } else {
        std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    }
}

void TowerManager::choosePreviousPriority(Vector2 position) {
    Tower* tower = getTowerFromPosition(position);
    if (tower) {
        tower->targetPriority = static_cast<TargetPriority>((static_cast<int>(tower->targetPriority) + 3) % 4);
    } else {
        std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    }
}