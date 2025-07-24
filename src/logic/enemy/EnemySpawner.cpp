#include "EnemySpawner.h"   

// headers of enemies
#include "enemies/Red.h"
#include "enemies/Blue.h"
#include "enemies/Green.h"
#include "enemies/Yellow.h"
#include "enemies/Pink.h"
#include "enemies/Black.h"
#include "enemies/White.h"
#include "enemies/Purple.h"
#include "enemies/Lead.h"
#include "enemies/Zebra.h"
#include "enemies/Rainbow.h"
#include "enemies/Ceramic.h"
#include "enemies/Moab.h"
#include "enemies/Bfb.h"
#include "enemies/Zomg.h"
#include "enemies/Ddt.h"
#include "enemies/Bad.h"

EnemySpawner::EnemySpawner() {
    /**
     * Technical issue:
     * Currently cant use constructor to initialize enemy templates
     * because the texture manager is not ready yet.
     */


    // Initialize enemy templates
    init();
}

EnemySpawner::EnemySpawner(const EnemySpawner& other) {
    if (this != &other) {
        // Clear current enemy templates
        enemyTemplates.clear();

        // deep copy of enemy templates
        for (const auto& [type, enemy] : other.enemyTemplates) {
            enemyTemplates[type] = enemy->clone(); // Clone each enemy template
        }

        // Clear current enemy children templates
        enemyChildrenTemplates.clear();

        // deep copy of enemy children templates
        for (const auto& [type, children] : other.enemyChildrenTemplates) {
            std::vector<std::unique_ptr<Enemy>> clonedChildren;
            for (const auto& child : children) {
                clonedChildren.push_back(child->clone()); // Clone each child enemy
            }
            enemyChildrenTemplates[type] = std::move(clonedChildren); // Move the cloned children
        }

        // Clear current regrow enemy templates
        regrowEnemyTemplates.clear();
        
        // deep copy of regrow enemy templates
        for (const auto& [type, enemy] : other.regrowEnemyTemplates) {
            regrowEnemyTemplates[type] = enemy->clone(); // Clone each regrow enemy template
        }
    } else {
        // should not be here
        std::cerr << "EnemySpawner copy constructor called on self-assignment." << std::endl;
    }
}

EnemySpawner& EnemySpawner::operator=(const EnemySpawner& other) {
    if (this != &other) {
        // Clear current enemy templates
        enemyTemplates.clear();

        // deep copy of enemy templates
        for (const auto& [type, enemy] : other.enemyTemplates) {
            enemyTemplates[type] = enemy->clone(); // Clone each enemy template
        }

        // Clear current enemy children templates
        enemyChildrenTemplates.clear();

        // deep copy of enemy children templates
        for (const auto& [type, children] : other.enemyChildrenTemplates) {
            std::vector<std::unique_ptr<Enemy>> clonedChildren;
            for (const auto& child : children) {
                clonedChildren.push_back(child->clone()); // Clone each child enemy
            }
            enemyChildrenTemplates[type] = std::move(clonedChildren); // Move the cloned children
        }

        // Clear current regrow enemy templates
        regrowEnemyTemplates.clear();

        // deep copy of regrow enemy templates
        for (const auto& [type, enemy] : other.regrowEnemyTemplates) {
            regrowEnemyTemplates[type] = enemy->clone(); // Clone each regrow enemy template
        }
    } else {
        // should not be here
        std::cerr << "EnemySpawner assignment operator called on self-assignment." << std::endl;
    }
    return *this;
}

std::unique_ptr<EnemySpawner> EnemySpawner::clone() const {
    return std::make_unique<EnemySpawner>(*this);
}

// Initialize enemy templates
void EnemySpawner::init() {
    // Enemy templates
    enemyTemplates[BloonType::Red] = std::make_unique<Red>();
    enemyTemplates[BloonType::Blue] = std::make_unique<Blue>();
    enemyTemplates[BloonType::Green] = std::make_unique<Green>();
    enemyTemplates[BloonType::Yellow] = std::make_unique<Yellow>();
    enemyTemplates[BloonType::Pink] = std::make_unique<Pink>();
    enemyTemplates[BloonType::Black] = std::make_unique<Black>();
    enemyTemplates[BloonType::White] = std::make_unique<White>();
    enemyTemplates[BloonType::Purple] = std::make_unique<Purple>();
    enemyTemplates[BloonType::Lead] = std::make_unique<Lead>();
    enemyTemplates[BloonType::Zebra] = std::make_unique<Zebra>();
    enemyTemplates[BloonType::Rainbow] = std::make_unique<Rainbow>();
    enemyTemplates[BloonType::Ceramic] = std::make_unique<Ceramic>();
    enemyTemplates[BloonType::Moab] = std::make_unique<Moab>();
    enemyTemplates[BloonType::Bfb] = std::make_unique<Bfb>();
    enemyTemplates[BloonType::Zomg] = std::make_unique<Zomg>();
    enemyTemplates[BloonType::Ddt] = std::make_unique<Ddt>();
    enemyTemplates[BloonType::Bad] = std::make_unique<Bad>();

    // Children enemies templates
    std::vector<std::unique_ptr<Enemy>> children;

    // Normal bloon
    enemyChildrenTemplates[BloonType::Red] = std::move(children); 

    children.push_back(std::make_unique<Red>()); 
    enemyChildrenTemplates[BloonType::Blue] = std::move(children);

    children.push_back(std::make_unique<Blue>());
    enemyChildrenTemplates[BloonType::Green] = std::move(children);

    children.push_back(std::make_unique<Green>());
    enemyChildrenTemplates[BloonType::Yellow] = std::move(children);

    children.push_back(std::make_unique<Yellow>());
    enemyChildrenTemplates[BloonType::Pink] = std::move(children);

    children.push_back(std::make_unique<Pink>());
    children.push_back(std::make_unique<Pink>());
    enemyChildrenTemplates[BloonType::Black] = std::move(children); 
    
    children.push_back(std::make_unique<Pink>());
    children.push_back(std::make_unique<Pink>());
    enemyChildrenTemplates[BloonType::White] = std::move(children);
    
    children.push_back(std::make_unique<Pink>());
    children.push_back(std::make_unique<Pink>());
    enemyChildrenTemplates[BloonType::Purple] = std::move(children);

    children.push_back(std::make_unique<Black>());
    children.push_back(std::make_unique<Black>());
    enemyChildrenTemplates[BloonType::Lead] = std::move(children);
    
    children.push_back(std::make_unique<Black>());
    children.push_back(std::make_unique<White>());
    enemyChildrenTemplates[BloonType::Zebra] = std::move(children);

    children.push_back(std::make_unique<Zebra>());
    children.push_back(std::make_unique<Zebra>());
    enemyChildrenTemplates[BloonType::Rainbow] = std::move(children);

    children.push_back(std::make_unique<Rainbow>());
    children.push_back(std::make_unique<Rainbow>());
    enemyChildrenTemplates[BloonType::Ceramic] = std::move(children);

    children.push_back(std::make_unique<Ceramic>());
    children.push_back(std::make_unique<Ceramic>());
    children.push_back(std::make_unique<Ceramic>());
    children.push_back(std::make_unique<Ceramic>());
    enemyChildrenTemplates[BloonType::Moab] = std::move(children);

    children.push_back(std::make_unique<Moab>());
    children.push_back(std::make_unique<Moab>());
    children.push_back(std::make_unique<Moab>());
    children.push_back(std::make_unique<Moab>());
    enemyChildrenTemplates[BloonType::Bfb] = std::move(children);

    children.push_back(std::make_unique<Bfb>());
    children.push_back(std::make_unique<Bfb>());
    children.push_back(std::make_unique<Bfb>());
    children.push_back(std::make_unique<Bfb>());
    enemyChildrenTemplates[BloonType::Zomg] = std::move(children);

    children.push_back(std::make_unique<Ceramic>());
    children.push_back(std::make_unique<Ceramic>());
    children.push_back(std::make_unique<Ceramic>());
    children.push_back(std::make_unique<Ceramic>());
    enemyChildrenTemplates[BloonType::Ddt] = std::move(children);

    children.push_back(std::make_unique<Zomg>());
    children.push_back(std::make_unique<Zomg>());
    children.push_back(std::make_unique<Ddt>());
    children.push_back(std::make_unique<Ddt>());
    children.push_back(std::make_unique<Ddt>());
    enemyChildrenTemplates[BloonType::Bad] = std::move(children);

    // Regrow enemies templates
    regrowEnemyTemplates[BloonType::Red] = std::make_unique<Blue>();
    regrowEnemyTemplates[BloonType::Blue] = std::make_unique<Green>();
    regrowEnemyTemplates[BloonType::Green] = std::make_unique<Yellow>();
    regrowEnemyTemplates[BloonType::Yellow] = std::make_unique<Pink>();
    regrowEnemyTemplates[BloonType::Pink] = std::make_unique<Black>();
    regrowEnemyTemplates[BloonType::Black] = std::make_unique<White>();
    regrowEnemyTemplates[BloonType::White] = std::make_unique<Purple>();
    regrowEnemyTemplates[BloonType::Purple] = std::make_unique<Lead>();
    regrowEnemyTemplates[BloonType::Lead] = std::make_unique<Zebra>();
    regrowEnemyTemplates[BloonType::Zebra] = std::make_unique<Rainbow>();
    regrowEnemyTemplates[BloonType::Rainbow] = std::make_unique<Ceramic>();
}

std::unique_ptr<Enemy> EnemySpawner::getEnemy(BloonType type, BloonProperties properties, Vector2 position, int pathIndex, EnemyModifies modifies) {
    auto it = enemyTemplates.find(type);
    if (it != enemyTemplates.end()) {
        std::unique_ptr<Enemy> enemy = it->second->clone();
        enemy->properties = properties;
        enemy->position = position; 
        // enemy->trackIndex = 0; 
        enemy->pathIndex = pathIndex; 
        enemy->setModifies(modifies); 
        enemy->loadTexture();

        return enemy;
    }

    // should not be here
    std::cerr << "Enemy type not found: " << static_cast<int>(type) << std::endl;
    return nullptr;
}

std::vector<std::unique_ptr<Enemy>> EnemySpawner::getChildrenEnemies(Enemy* enemy, EnemyModifies modifies) {
    if (!enemy) return {};

    auto it = enemyChildrenTemplates.find(enemy->type);
    if (it != enemyChildrenTemplates.end()) {
        std::vector<std::unique_ptr<Enemy>> childrenEnemies;

        for (const auto& child : it->second) {
            std::unique_ptr<Enemy> childEnemy = child->clone();
            childEnemy->regrowLimit = enemy->regrowLimit;
            // childEnemy->regrowTimer = 0.0f;
            childEnemy->properties = enemy->properties;
            childEnemy->position = enemy->position;
            childEnemy->trackIndex = enemy->trackIndex;
            childEnemy->pathIndex = enemy->pathIndex;
            childEnemy->setModifies(modifies);
            childEnemy->loadTexture();

            childrenEnemies.push_back(std::move(childEnemy));
        }

        return childrenEnemies;
    }

    std::cerr << "Children enemies type not found: " << static_cast<int>(enemy->type) << std::endl;
    return {};
}

void EnemySpawner::getRegrowEnemy(std::unique_ptr<Enemy>& enemy, EnemyModifies modifies) {
    if(!enemy) return;
    if(enemy->properties.isRegrow == false) return;
    if(enemy->type == enemy->regrowLimit) return; 
    if(enemy->regrowTimer < regrowTime) {
        enemy->regrowTimer += GetFrameTime(); 
        return; 
    }
    
    auto it = regrowEnemyTemplates.find(enemy->type);
    if (it != regrowEnemyTemplates.end()) {
        std::unique_ptr<Enemy> regrowEnemy = it->second->clone();
        regrowEnemy->regrowLimit = enemy->regrowLimit; 
        regrowEnemy->properties = enemy->properties; 
        regrowEnemy->position = enemy->position; 
        regrowEnemy->trackIndex = enemy->trackIndex;
        regrowEnemy->pathIndex = enemy->pathIndex;

        regrowEnemy->setModifies(modifies);
        regrowEnemy->loadTexture();

        // Replace the original enemy with the regrow enemy
        enemy = std::move(regrowEnemy);
        return;
    } 

    // should not be here
    std::cerr << "Regrow enemy type not found: " << static_cast<int>(enemy->type) << std::endl;
}