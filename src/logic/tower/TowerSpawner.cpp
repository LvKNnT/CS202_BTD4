
#include "TowerSpawner.h"
#include <iostream>

#include "../skill/Skill.h"

// headers of towers
#include "towers/dartmonkey/DartMonkey.h"
#include "towers/bombshooter/BombShooter.h"
#include "towers/ninjamonkey/NinjaMonkey.h"
#include "towers/snipermonkey/SniperMonkey.h"
#include "towers/tackshooter/TackShooter.h"
#include "towers/boomerangmonkey/BoomerangMonkey.h"
#include "towers/icemonkey/IceMonkey.h"
#include "towers/monkeysub/MonkeySub.h"

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
    towerTemplates[TowerType::BombShooter] = std::make_unique<BombShooter>();
    towerTemplates[TowerType::NinjaMonkey] = std::make_unique<NinjaMonkey>();
    towerTemplates[TowerType::SniperMonkey] = std::make_unique<SniperMonkey>();
    towerTemplates[TowerType::TackShooter] = std::make_unique<TackShooter>();
    towerTemplates[TowerType::BoomerangMonkey] = std::make_unique<BoomerangMonkey>();
    towerTemplates[TowerType::IceMonkey] = std::make_unique<IceMonkey>();
    towerTemplates[TowerType::MonkeySub] = std::make_unique<MonkeySub>();
};  

void TowerSpawner::init(TowerModifies modifies) {
    // Initialize tower templates with modifies
    towerTemplates[TowerType::DartMonkey] = std::make_unique<DartMonkey>();
    towerTemplates[TowerType::DartMonkey]->setModifies(modifies); // Set modifies for the Dart Monkey tower
    
    towerTemplates[TowerType::BombShooter] = std::make_unique<BombShooter>();
    towerTemplates[TowerType::BombShooter]->setModifies(modifies); // Set modifies for the Bomb Shooter tower

    towerTemplates[TowerType::NinjaMonkey] = std::make_unique<NinjaMonkey>();
    towerTemplates[TowerType::NinjaMonkey]->setModifies(modifies); // Set modifies for the Ninja Monkey tower

    towerTemplates[TowerType::SniperMonkey] = std::make_unique<SniperMonkey>();
    towerTemplates[TowerType::SniperMonkey]->setModifies(modifies); // Set modifies for the Sniper Monkey tower

    towerTemplates[TowerType::TackShooter] = std::make_unique<TackShooter>();
    towerTemplates[TowerType::TackShooter]->setModifies(modifies); // Set modifies for the Tack Shooter tower

    towerTemplates[TowerType::BoomerangMonkey] = std::make_unique<BoomerangMonkey>();
    towerTemplates[TowerType::BoomerangMonkey]->setModifies(modifies); // Set modifies for the Boomerang Monkey tower

    towerTemplates[TowerType::IceMonkey] = std::make_unique<IceMonkey>();
    towerTemplates[TowerType::IceMonkey]->setModifies(modifies); // Set modifies for the Ice Monkey tower

    towerTemplates[TowerType::MonkeySub] = std::make_unique<MonkeySub>();
    towerTemplates[TowerType::MonkeySub]->setModifies(modifies); // Set modifies for the Monkey Sub tower

};

std::unique_ptr<Tower> TowerSpawner::getTower(TowerType type, Vector2 position, int towerID, const TowerModifies& modifies) {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        it->second->loadTexture(); // Load the texture for the tower

        // Create a new tower instance using the template
        std::unique_ptr<Tower> tower = it->second->clone();
        tower->position = position; 
        tower->towerId = towerID; 

        for(auto& attack : tower->attacks) {
            attack->towerId = towerID; 
            attack->position = position; 
        }
        tower->setModifies(modifies); 

        return tower;
    } else {
        // should not be here
        std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
        return nullptr; // Return nullptr if the type is not found
    }
}

std::unique_ptr<Tower> TowerSpawner::getPutTower(TowerType type, Vector2 position, const TowerModifies& modifies) {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        it->second->loadTexture(); // Load the texture for the tower

        // Create a new tower instance using the template
        std::unique_ptr<Tower> tower = it->second->clone();
        tower->position = position; 

        for(auto& attack : tower->attacks) {
            attack->position = position; 
        }
        tower->setModifies(modifies);

        return tower;
    } else {
        // should not be here
        std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
        return nullptr; // Return nullptr if the type is not found
    }
}

std::unique_ptr<Tower> TowerSpawner::getTower(TowerType type, Vector2 position, float rotation, int towerID, const TowerModifies& modifies) {
    // Find the tower template for the given type
    auto it = towerTemplates.find(type);
    if (it != towerTemplates.end()) {
        it->second->loadTexture(); // Load the texture for the tower

        // Create a new tower instance using the template
        std::unique_ptr<Tower> tower = it->second->clone();
        tower->position = position; 
        tower->rotation = rotation;
        tower->towerId = towerID; 

        for(auto& attack : tower->attacks) {
            attack->towerId = towerID; 
            attack->position = position; 
        }
        tower->setModifies(modifies); 

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
    }
    
    // std::cerr << "Tower type not found: " << static_cast<int>(type) << std::endl;
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
