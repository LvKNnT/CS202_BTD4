#include "TowerManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

#include "../skill/Skill.h"
#include "../../interfaces/audio/MyAudio.h"
#include "towers/ninjamonkey/NinjaMonkey.h"

// hero includes
#include "../hero/heroes/Quincy.h"
#include "../hero/heroes/Benjamin.h"
#include "../hero/heroes/Rosalia.h"
#include "../hero/heroes/Etienne.h"

TowerManager::TowerManager(TowerModifies modifies)
    : currentModifies(modifies), towerIDCounter(0) {
    towerSpawner = nullptr;
}

TowerManager::TowerManager(HeroType heroType, TowerModifies modifies)
    : currentHeroType(heroType), currentModifies(modifies), towerIDCounter(0) {
    // Initialize unique_ptr
    towerSpawner = std::make_unique<TowerSpawner>(currentModifies, heroType);
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

        putTower = other.putTower ? other.putTower->clone() : nullptr; // Clone the put tower if it exists
        lastPickedTower = other.lastPickedTower; // Copy the last picked tower
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

        putTower = other.putTower ? other.putTower->clone() : nullptr; // Clone the put tower if it exists
        lastPickedTower = other.lastPickedTower; // Copy the last picked tower
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

void TowerManager::spawnPutTower(TowerType type, Vector2 position) {
    std::unique_ptr<Tower> tower = towerSpawner->getPutTower(type, position, currentModifies);

    putTower = nullptr;
    if (tower) {
        putTower = std::move(tower);
    }
    else std::cerr << "Failed to spawn put tower of type: " << static_cast<int>(type) << std::endl;
}

void TowerManager::unPutTower() {
    if (putTower) {
        putTower = nullptr; // Clear the put tower
    }
}

void TowerManager::spawnTower(TowerType type, Vector2 position, float rotation) {
    std::unique_ptr<Tower> tower = towerSpawner->getTower(type, position, rotation, towerIDCounter++, currentModifies);

    if (tower) {
        towerList.push_back(std::move(tower));
    } else {
        std::cerr << "Failed to spawn tower of type: " << static_cast<int>(type) << std::endl;
    }
}

void TowerManager::pickTower(Vector2 position) {
    std::weak_ptr<Tower> tower = getTowerFromPosition(position);
    if (auto towerPtr = tower.lock()) {
        lastPickedTower = towerPtr; // Set the last picked tower
        std::cout << "Picked tower: " << static_cast<int>(towerPtr->type) << std::endl;
    } else {
        lastPickedTower.reset(); // Clear the last picked tower if none found
        std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    }
}

void TowerManager::unPickTower() {
    if (lastPickedTower.lock()) {
        lastPickedTower.reset(); // Clear the last picked tower
        std::cout << "Unpicked tower." << std::endl;
    } else {
        std::cerr << "No tower was picked to unpick." << std::endl;
    }
}

LogicInfo TowerManager::getInfo() const {
    if(lastPickedTower.lock()) {
        return lastPickedTower.lock()->getInfo();
    }
    
    return LogicInfo(); // Return an empty LogicInfo if no tower is picked
}

LogicInfo TowerManager::getInfoTower(TowerType type) const {
    return towerSpawner->getInfoTower(type, currentModifies);
}

LogicInfo TowerManager::getInfoTower(Vector2 position) const {
    std::weak_ptr<Tower> tower = getTowerFromPosition(position);
    if (auto towerPtr = tower.lock()) {
        return towerPtr->getInfo();
    }

    std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    return LogicInfo(); // Return an empty LogicInfo if no tower is found
}

LogicInfo TowerManager::getHeroInfo() const {
    if (towerSpawner && towerSpawner->hero) {
        return towerSpawner->hero->getInfo();
    }
    return LogicInfo(); // Return an empty LogicInfo if no hero is set
}

void TowerManager::drawTowers() const {
    for (const auto& tower : towerList) {
        if (tower) {
            if(lastPickedTower.lock() && lastPickedTower.lock() == tower) {
                tower->drawRange(); 
            } 
            tower->draw(); 
        } else {
            std::cerr << "Tower is null." << std::endl;
        }
    }

    if(putTower) {
        putTower->drawPut();
        putTower->draw();
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

    updateNinjaTower();
}

void TowerManager::updateNinjaTower() {
    std::vector<std::shared_ptr<Tower>> ninjas;
    for(const auto &tower:towerList) {
        if(tower->type != TowerType::NinjaMonkey) continue;
        ninjas.push_back(tower); 
    }

    for(const auto &ninja:ninjas) {
        std::dynamic_pointer_cast<NinjaMonkey>(ninja)->activateShinobiTactics();
        if(!std::dynamic_pointer_cast<NinjaMonkey>(ninja)->getHasShinobiTactics()) {
            continue;
        }

        for(const auto &otherNinja:ninjas) {
            auto tmpNinjaPtr = std::dynamic_pointer_cast<NinjaMonkey>(ninja);
            if(tmpNinjaPtr->addApplideShinobiTactics(std::dynamic_pointer_cast<NinjaMonkey>(otherNinja)->towerId)) {
                // can be added
                if(Utils::isInCirlceRange(tmpNinjaPtr->position, 120.0, std::dynamic_pointer_cast<NinjaMonkey>(otherNinja)->position)) {
                    std::dynamic_pointer_cast<NinjaMonkey>(otherNinja)->addShinobiStatck();
                }
            }
        }
    }
}

std::weak_ptr<Tower> TowerManager::getTowerFromPosition(Vector2 position) const {
    for (const auto& tower : towerList) {
        if (tower && CheckCollisionPointRec(position, tower->getBoundingBox())) {
            return std::weak_ptr<Tower>(tower); // Return a weak pointer to the tower at the position
        }
    }
    return std::weak_ptr<Tower>(); // Return an empty weak pointer if no tower is found
}

void TowerManager::chooseNextPriority() {
    if (auto towerPtr = lastPickedTower.lock()) {
        towerPtr->targetPriority = static_cast<TargetPriority>((static_cast<int>(towerPtr->targetPriority) + 1) % 4);
        
        for(auto& attack : towerPtr->attacks) {
            attack->getProperties().targetPriority = towerPtr->targetPriority; // Update the attack's target priority
        }
    }
}

void TowerManager::chooseNextPriority(Vector2 position) {
    std::weak_ptr<Tower> tower = getTowerFromPosition(position);
    if (auto towerPtr = tower.lock()) {
        towerPtr->targetPriority = static_cast<TargetPriority>((static_cast<int>(towerPtr->targetPriority) + 1) % 4);

        for(auto& attack : towerPtr->attacks) {
            attack->getProperties().targetPriority = towerPtr->targetPriority; // Update the attack's target priority
        }
    } 
    else {
        std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    }
}

void TowerManager::choosePreviousPriority() {
    if (auto towerPtr = lastPickedTower.lock()) {
        towerPtr->targetPriority = static_cast<TargetPriority>((static_cast<int>(towerPtr->targetPriority) + 3) % 4);

        for(auto& attack : towerPtr->attacks) {
            attack->getProperties().targetPriority = towerPtr->targetPriority; // Update the attack's target priority
        }
    }
}

void TowerManager::choosePreviousPriority(Vector2 position) {
    std::weak_ptr<Tower> tower = getTowerFromPosition(position);
    if (auto towerPtr = tower.lock()) {
        towerPtr->targetPriority = static_cast<TargetPriority>((static_cast<int>(towerPtr->targetPriority) + 3) % 4);

        for(auto& attack : towerPtr->attacks) {
            attack->getProperties().targetPriority = towerPtr->targetPriority; // Update the attack's target priority
        }
    } 
    else {
        std::cerr << "No tower found at position: " << position.x << ", " << position.y << std::endl;
    }
}

int TowerManager::sellTower() {
    auto towerPtr = lastPickedTower.lock();
    if (!towerPtr) {
        std::cerr << "No tower selected to sell." << std::endl;
        return 0; // No tower to sell
    }

    // handle selling Ninja Tower
    if(towerPtr->type == TowerType::NinjaMonkey) {
        handleSellNinjaTower(towerPtr);
    }

    int sellValue = std::stoi(towerPtr->getInfo()["sell"]);

    // Remove the tower from the list
    auto it = std::remove_if(towerList.begin(), towerList.end(),
        [&towerPtr](const std::shared_ptr<Tower>& tower) {
            return tower && tower->towerId == towerPtr->towerId; // Match by tower ID
        });
    towerList.erase(it, towerList.end());

    lastPickedTower.reset(); // Clear the last picked tower
    return sellValue; // Return the sell value
}

void TowerManager::handleSellNinjaTower(std::shared_ptr<Tower> towerPtr) {
    if(!std::dynamic_pointer_cast<NinjaMonkey>(towerPtr)->getHasShinobiTactics()) {
        return;
    }

    std::vector<std::shared_ptr<Tower>> ninjas;
    for(const auto &tower:towerList) {
        if(tower->type != TowerType::NinjaMonkey) continue;
        ninjas.push_back(tower); 
    }

    for(const auto &otherNinja:ninjas) {
        if(!std::dynamic_pointer_cast<NinjaMonkey>(towerPtr)->addApplideShinobiTactics(std::dynamic_pointer_cast<NinjaMonkey>(otherNinja)->towerId)) {
            // can be deleted
            std::dynamic_pointer_cast<NinjaMonkey>(otherNinja)->delShinobiStack();
        }
    }
}

void TowerManager::save(const std::string& filePath) const {
    std::fstream file(filePath, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for saving towers." << std::endl;
        return;
    } 

    file << static_cast<int>(currentHeroType) << std::endl; // Save hero type

    // file << "towers\n"; 
    file << towerList.size() << std::endl; // Save the number of towers
    
    for (const auto& tower : towerList) {
        if (tower) {
            file << static_cast<int>(tower->type) << " " << tower->position.x << " " << tower->position.y 
                    << " " << tower->rotation << " " << static_cast<int>(tower->targetPriority) << " "
                    << tower->upgradeTop->getName() << " : " << tower->upgradeMiddle->getName() << " : " << tower->upgradeBottom->getName() << " : ";
            
            if(tower->skill) {
                file << tower->skill->getCooldown() << " " << tower->skill->getISkillsActivating() << " ";
            } else file << "-1  -1 ";

            if(tower->passiveSkills.empty()) {
                file << std::endl;
            }

            for(const auto &skill:tower->passiveSkills) {
                file << skill->getTimer() << " " << skill->getISkillsActivating() << std::endl;
            }
            
        } else {
            std::cerr << "Tower is null during save." << std::endl;
        }
    }
    file.close();
}

void TowerManager::load(const std::string& filePath) {
    std::fstream file(filePath, std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error: Failed to open file for loading towers." << std::endl;
        return;
    }

    // skip 3 lines
    std::string line;
    std::getline(file, line);
    std::getline(file, line);
    std::getline(file, line);

    int currentHeroTypeInt;
    file >> currentHeroTypeInt; // Load hero type
    currentHeroType = static_cast<HeroType>(currentHeroTypeInt);
    towerSpawner = std::make_unique<TowerSpawner>(currentModifies, currentHeroType);

    int towerCount;
    file >> towerCount; // Read the number of towers

    std::cerr << "Loading " << towerCount << " towers." << std::endl;

    for (int i = 0; i < towerCount; ++i) {
        int typeInt;
        Vector2 position;
        float rotation;
        int _targetPriority;
        std::string _upgradeTop = "", _upgradeMiddle = "", _upgradeBottom = "";
        std::string skillTimer = "", skillIsSkillActivating = "", _passiveSkills = "";

        file >> typeInt >> position.x >> position.y >> rotation;
        file >> _targetPriority;
        std::string tmp;
        while(file >> tmp) {
            if(tmp == ":") break;
            _upgradeTop += (_upgradeTop.empty() ? "":" ") + tmp;
        }

        while(file >> tmp) {
            if(tmp == ":") break;
            _upgradeMiddle += (_upgradeMiddle.empty() ? "":" ") + tmp;
        }

        while(file >> tmp) {
            if(tmp == ":") break;
            _upgradeBottom += (_upgradeBottom.empty() ? "":" ") + tmp;
        }

        file >> skillTimer >> skillIsSkillActivating;
        getline(file, _passiveSkills);

        std::cerr << "Loading tower type: " << typeInt << " at position: (" 
                    << position.x << ", " << position.y << ") with rotation: " 
                    << rotation << " with TargePriority: " << _targetPriority 
                    << " with upgrades: " << _upgradeTop << " : " << _upgradeMiddle << " : " << _upgradeBottom << std::endl; 

        TowerType type = static_cast<TowerType>(typeInt);
        spawnTower(type, position, rotation); 
        
        // Save the Target Priority
        towerList.back()->targetPriority = static_cast<TargetPriority>(_targetPriority);
        // Save upgrades to new tower
        towerList.back()->savedInfo["nextUpgradeTop"] = _upgradeTop;
        towerList.back()->savedInfo["nextUpgradeMiddle"] = _upgradeMiddle;
        towerList.back()->savedInfo["nextUpgradeBottom"] = _upgradeBottom;
        towerList.back()->savedInfo["skillTimer"] = skillTimer;
        towerList.back()->savedInfo["skillIsSkillActivating"] = skillIsSkillActivating;
        towerList.back()->savedInfo["passiveSkills"] = _passiveSkills;
    }
    file.close();
}