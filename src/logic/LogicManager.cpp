#include "LogicManager.h"

#include "raymath.h"

#include <cfloat>
#include <algorithm>
#include <fstream>

#include "skill/Skill.h"
#include "../interfaces/audio/MyAudio.h"

void LogicManager::updateEnemies(EnemyManager& enemyManager, MapManager& mapManager, ResourceManager& resourceManager) {
    for (auto it = enemyManager.enemyList.begin(); it != enemyManager.enemyList.end(); ) {
        int result = runEnemy(**it, mapManager.getCurrentMap());
        
        if (result == -1) {
            // Enemy reached the end — remove and destroy it
            resourceManager.currentResource.lives -= (*it)->livesLost; // Update lives lost
            it = enemyManager.enemyList.erase(it);  // erase returns the next iterator
            continue;  // Skip the increment, already moved to next
        }
        ++it;
    }

    sortEnemyList(enemyManager, mapManager.getCurrentMap()); 
}

// Logic to move the enemy along the path
int LogicManager::runEnemy(Enemy& enemy, const Map& map) {
    if(map.isLastPoint(enemy.trackIndex, enemy.pathIndex)) {
        // Enemy has reached the end of the path
        enemy.die(); // Handle the death of the enemy
        return -1; // Indicating that the enemy has reached the end of the path
    }

    float elapsedTime = GetFrameTime();
    Vector2 position = enemy.position;
    int trackIndex = enemy.trackIndex;
    int pathIndex = enemy.pathIndex; 
    int speed;
    if(enemy.debuff.knockbackChance < 100) { // Ninja - Distraction
        speed = enemy.debuff.calNinjaDistractionKnockbackSpeed(enemy.speed);
        if(enemy.type == BloonType::Ceramic) speed /= 2;
    }
    else {
        speed = enemy.debuff.calSpeed(enemy.speed) + enemy.debuff.calKnockbackSpeed(enemy.speed);
    }

    Vector2 nextPoint = map.getNextPoint(trackIndex, pathIndex);
    Vector2 direction = {nextPoint.x - position.x, nextPoint.y - position.y};
    float distance = Vector2Distance(position, nextPoint);

    // If speed is zero, don't move
    if (speed == 0) {
        direction = {0, 0};
    } else if (speed > 0) {
        // Move forward along the path
        while (elapsedTime > 0.0f && !map.isLastPoint(trackIndex, pathIndex)) {
            nextPoint = map.getNextPoint(trackIndex, pathIndex);
            direction = {nextPoint.x - position.x, nextPoint.y - position.y};
            distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

            if (speed * elapsedTime < distance) {
                position.x += direction.x / distance * speed * elapsedTime;
                position.y += direction.y / distance * speed * elapsedTime;
                elapsedTime = 0.0f;
            } else {
                position = nextPoint;
                trackIndex++;
                elapsedTime -= distance / speed;
            }

            if (map.isLastPoint(trackIndex, pathIndex)) {
                enemy.position = position;
                enemy.trackIndex = trackIndex;
                enemy.die();
                return -1;
            }
        }
    } else {
        // Move backward along the path
        speed = -speed; // Make speed positive for calculation
        while (elapsedTime > 0.0f && trackIndex > 0) {
            Vector2 prevPoint = map.getCurrentPoint(trackIndex, pathIndex);
            direction = {prevPoint.x - position.x, prevPoint.y - position.y};
            distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

            if (speed * elapsedTime < distance) {
                position.x += direction.x / distance * speed * elapsedTime;
                position.y += direction.y / distance * speed * elapsedTime;
                elapsedTime = 0.0f;
            } else {
                position = prevPoint;
                trackIndex--;
                elapsedTime -= distance / speed;
            }
            // If we reach the start of the path, stop
            if (trackIndex == 0) {
                break;
            }
        }
        // Restore speed sign if needed elsewhere
        speed = -speed;
    }

    // Before returning, update the enemy's position and track index
    enemy.position = position; 
    enemy.trackIndex = trackIndex; 
    enemy.setRotation(atan2f(direction.y, direction.x) * (180.0f / PI)); // Set the rotation based on the direction

    if(static_cast<int>(enemy.type) < 12) { // for normal bloons
        enemy.isActiveFlag = map.getPointType(trackIndex, pathIndex) != Point::Type::Invisible; // Check if the enemy is still active based on the point type
    }
    else enemy.isActiveFlag = true; // for moab class

    // If the enemy has not reached the end of the path, return 0
    return 0;
}

void LogicManager::sortEnemyList(EnemyManager& enemyManager, const Map& map) {
    // Sort the enemy list based on their position in the path
    std::sort(enemyManager.enemyList.begin(), enemyManager.enemyList.end(), 
        [&map](const std::unique_ptr<Enemy>& a, const std::unique_ptr<Enemy>& b) {
            return map.distanceToEndPoint(a->getPosition(), a->trackIndex, a->pathIndex) < 
                   map.distanceToEndPoint(b->getPosition(), b->trackIndex, b->pathIndex);
        });
}

void LogicManager::updateBullets(BulletManager& bulletManager) {
    for(auto it = bulletManager.bulletList.begin(); it != bulletManager.bulletList.end(); ) {
        // Check if the bullet is still on the map
        int result = (*it)->run();

        if (result == -1) {
            // Bullet has reached the end of its life — remove and destroy it
            it = bulletManager.bulletList.erase(it);  // erase returns the next iterator
            continue;  // Skip the increment, already moved to next
        }
        
        // Update the life span of the bullet
        (*it)->lifeSpan -= GetFrameTime();
        
        if ((*it)->lifeSpan <= 0) {
            // Bullet has reached the end of its life span — remove and destroy it
            
            // first, remove all pierce left
            (*it)->pierce = 0; 
            std::vector<std::unique_ptr<Bullet>> bulletChildren = (*it)->getChild();
            
            it = bulletManager.bulletList.erase(it);  // erase returns the next iterator

            if (!bulletChildren.empty()) {
                it = bulletManager.bulletList.insert(it,
                    std::make_move_iterator(bulletChildren.begin()), 
                    std::make_move_iterator(bulletChildren.end()));
            }

            continue;  // Skip the increment, already moved to next
        }

        ++it;
    }
}

void LogicManager::updateBulletsHitEnemies(BulletManager& bulletManager, EnemyManager& enemyManager, TowerManager& towerManager, MapManager& mapManager, ResourceManager& resourceManager) {
    for (auto bulletIt = bulletManager.bulletList.begin(); bulletIt != bulletManager.bulletList.end(); ) {
        bool isBulletAlive = true;
        
        std::set<int> hitEnemies;
        for (auto enemyIt = enemyManager.enemyList.begin(); enemyIt != enemyManager.enemyList.end() && isBulletAlive; ) {
            if((*enemyIt)->isActiveFlag == false) {
                ++enemyIt; 
                continue;
            }

            // bullet goes through enemies section 
            if((*bulletIt)->properties.canCamo == false && (*enemyIt)->properties.isCamo && !(*bulletIt)->attackBuff.canStripCamo) {
                ++enemyIt; 
                continue;
            }
            if((*bulletIt)->hitEnemies.find((*enemyIt)->enemyId) != (*bulletIt)->hitEnemies.end()) {
                // Bullet has already hit this enemy
                // std::cerr << "Bullet " << (*bulletIt)->tag << " has already hit enemy " << (*enemyIt)->tag << " id " << (*enemyIt)->enemyId << " with lifeSpan" << (*bulletIt)->lifeSpan << std::endl;
                ++enemyIt; 
                continue;
            }
            
            if (checkCollision(**bulletIt, **enemyIt)) {
                // bullet touch but cannot destroy enemy
                if(!canBulletDestroyEnemy(**bulletIt, **enemyIt)) {
                    bulletIt = bulletManager.bulletList.erase(bulletIt);
                    isBulletAlive = false;
                    continue;
                }

                // mark the enemy as hit by this bullet
                // std::cerr << "Bullet " << (*bulletIt)->tag << " hit enemy " << (*enemyIt)->tag << " id " << (*enemyIt)->enemyId << " with lifeSpan " << (*bulletIt)->lifeSpan << std::endl;
                // (*bulletIt)->hitEnemies.insert((*enemyIt)->enemyId);
                hitEnemies.insert((*enemyIt)->enemyId);
                
                // Apply the debuff to the enemy
                (*enemyIt)->setDebuff((*bulletIt)->normalDebuff, (*bulletIt)->moabDebuff);

                int popCount = 0;
                std::vector<std::unique_ptr<Enemy>> enemyChildren;
                enemyChildren = getChildrenEnemies(enemyManager, **enemyIt, (*bulletIt)->damage, popCount, resourceManager);

                // Add the pop count to the original tower
                for (auto& tower : towerManager.towerList) {
                    if(tower->towerId == (*bulletIt)->towerId) {
                        tower->popCount += popCount; 
                    }
                }

                // Every collision costs bullet damage
                if((*enemyIt)->health <= 0) {
                    int index = std::distance(enemyManager.enemyList.begin(), enemyIt);

                    if (!enemyChildren.empty()) {
                        // First, shifting each children
                        for(int i=0; i < enemyChildren.size(); ++i) {
                            for(int j=0;j<i;++j) {
                                runEnemy(*enemyChildren[j], mapManager.getCurrentMap());
                            }
                        }

                        enemyManager.enemyList.insert(enemyManager.enemyList.begin() + index,
                            std::make_move_iterator(enemyChildren.begin()),
                            std::make_move_iterator(enemyChildren.end()));
                    }

                    enemyIt = enemyManager.enemyList.begin() + index + enemyChildren.size();
                    enemyIt = enemyManager.enemyList.erase(enemyIt);
                }
                else ++enemyIt;

                // Every collision cost 1 pierce
                bool isBulletDie = (*bulletIt)->hit(1);

                std::vector<std::unique_ptr<Bullet> > bulletChildren = (*bulletIt)->getChild();
                
                if(isBulletDie) {
                    bulletIt = bulletManager.bulletList.erase(bulletIt);
                    isBulletAlive = false;
                }
                
                if(!bulletChildren.empty()) {
                    if(isBulletDie) {
                        bulletIt = bulletManager.bulletList.insert(bulletIt,
                            std::make_move_iterator(bulletChildren.begin()), 
                            std::make_move_iterator(bulletChildren.end()));
                    } 
                    else {
                        bulletIt = bulletManager.bulletList.insert(std::next(bulletIt),
                            std::make_move_iterator(bulletChildren.begin()), 
                            std::make_move_iterator(bulletChildren.end()));
                        bulletIt = std::prev(bulletIt); 
                    }
                }
            }
            else ++enemyIt;
        }

        if(isBulletAlive && bulletIt != bulletManager.bulletList.end()) {
            (*bulletIt)->hitEnemies.insert(hitEnemies.begin(), hitEnemies.end()); 
            (*bulletIt)->update(enemyManager.enemyList); // Update the bullet tracing
            ++bulletIt;
        }
    }
}

bool LogicManager::canBulletDestroyEnemy(const Bullet& bullet, const Enemy& enemy) const {
    // camo
    if(!bullet.properties.canCamo && enemy.properties.isCamo) {
        return false;
    }

    // special properties
    if(bullet.properties.canLead == false
    && (enemy.type == BloonType::Lead || enemy.type == BloonType::Ddt)) {
        return false;
    }
    if(bullet.properties.canBlack == false
    && (enemy.type == BloonType::Black || enemy.type == BloonType::Zebra || enemy.type == BloonType::Ddt)) {
        return false;
    }
    if(bullet.properties.canWhite == false
    && (enemy.type == BloonType::White || enemy.type == BloonType::Zebra)) {
        return false;
    }
    if(bullet.properties.canFrozen == false
    && (enemy.properties.isFrozen)) {
        return false;
    }
    if(bullet.properties.canPurple == false
    && (enemy.type == BloonType::Purple)) {
        return false;
    }

    return true;
}

std::vector<std::unique_ptr<Enemy>> LogicManager::getChildrenEnemies(EnemyManager& enemyManager, Enemy& enemy, int damage, int& popCount, ResourceManager& resourceManager) const {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << enemy.tag << " hit with damage: " << damage << std::endl;
    flog.close();
    
    if(enemy.hit(damage)) {
        popCount += damage;
        return {};
    }

    resourceManager.currentResource.cash += enemy.reward; // Add reward for popping the enemy

    std::vector<std::unique_ptr<Enemy>> childrenEnemies;
    childrenEnemies = enemyManager.spawnChildrenEnemies(&enemy, resourceManager.currentResource.currentRound);
    
    int remainingHealth = -enemy.health; // Get the remaining health after damage
    int finalPopCount = damage - remainingHealth; // Calculate the pop count`
    popCount += finalPopCount;
    std::vector<std::unique_ptr<Enemy> > finalChildrenEnemies;

    for(auto& child : childrenEnemies) {
        std::vector<std::unique_ptr<Enemy> > subChildren = getChildrenEnemies(enemyManager, *child, remainingHealth, popCount, resourceManager);

        if(!subChildren.empty()) {
            // If there are sub-children, add them to the final list
            for(auto& subChild : subChildren) {
                finalChildrenEnemies.push_back(std::move(subChild));
            }
        } else if(child->health > 0) {
            // If no sub-children, just add the child
            finalChildrenEnemies.push_back(std::move(child));
        }
    }

    return finalChildrenEnemies;
}

bool LogicManager::checkCollision(const Bullet& bullet, const Enemy& enemy) const {
    Rectangle bulletBox = bullet.getBoundingBox();
    Rectangle enemyBox = enemy.getBoundingBox();

    // Separating Axis Theorem (SAT) for rectangle collision
    // Get the corners of both rectangles
    Vector2 bulletCorners[4], enemyCorners[4];
    // Get the four corners of the bullet and enemy rectangles
    auto getCorners = [](const Rectangle& rect, float rotation, Vector2* corners) {
        float halfWidth = rect.width / 2.0f;
        float halfHeight = rect.height / 2.0f;

        float cosTheta = cosf(rotation * (PI / 180.0f));
        float sinTheta = sinf(rotation * (PI / 180.0f));

        // Rotate corners around the center of the rectangle
        // Calculate the center of the rectangle
        float centerX = rect.x + halfWidth;
        float centerY = rect.y + halfHeight;

        // Define the four corners relative to the center
        corners[0] = {rect.x, rect.y}; // Top-left
        corners[1] = {rect.x + rect.width, rect.y}; // Top-right
        corners[2] = {rect.x + rect.width, rect.y + rect.height}; // Bottom-right
        corners[3] = {rect.x, rect.y + rect.height}; // Bottom-left

        // Rotate each corner around the center
        for (int i = 0; i < 4; ++i) {
            float x = corners[i].x - centerX;
            float y = corners[i].y - centerY;
            corners[i].x = centerX + x * cosTheta - y * sinTheta;
            corners[i].y = centerY + x * sinTheta + y * cosTheta;
        }
    };

    getCorners(bulletBox, bullet.rotation, bulletCorners);
    getCorners(enemyBox, enemy.rotation, enemyCorners);

    // Axes to test: normals of both rectangles' edges
    Vector2 axes[4];
    for (int i = 0; i < 2; ++i) {
        Vector2 edge = {bulletCorners[(i + 1) % 4].x - bulletCorners[i].x, bulletCorners[(i + 1) % 4].y - bulletCorners[i].y};
        axes[i] = { -edge.y, edge.x }; // Perpendicular
    }
    for (int i = 0; i < 2; ++i) {
        Vector2 edge = {enemyCorners[(i + 1) % 4].x - enemyCorners[i].x, enemyCorners[(i + 1) % 4].y - enemyCorners[i].y};
        axes[2 + i] = { -edge.y, edge.x };
    }

    // Normalize axes
    for (int i = 0; i < 4; ++i) {
        float len = sqrtf(axes[i].x * axes[i].x + axes[i].y * axes[i].y);
        axes[i].x /= len;
        axes[i].y /= len;
    }

    // Project both rectangles onto each axis and check for overlap
    for (int i = 0; i < 4; ++i) {
        float minA = FLT_MAX, maxA = -FLT_MAX;
        float minB = FLT_MAX, maxB = -FLT_MAX;
        for (int j = 0; j < 4; ++j) {
            float projA = bulletCorners[j].x * axes[i].x + bulletCorners[j].y * axes[i].y;
            minA = fminf(minA, projA);
            maxA = fmaxf(maxA, projA);
            float projB = enemyCorners[j].x * axes[i].x + enemyCorners[j].y * axes[i].y;
            minB = fminf(minB, projB);
            maxB = fmaxf(maxB, projB);
        }
        if (maxA < minB || maxB < minA) {
            // No overlap on this axis, so no collision
            return false;
        }
    }

    return true;
}

void LogicManager::updateTowers(TowerManager& towerManager, EnemyManager& enemyManager, BulletManager& bulletManager) {
    for(auto& tower : towerManager.towerList) {
        if(tower->isActive()) {
            // vector of enemies that are in range of the attack
            std::vector<Enemy*> enemiesInRange;

            for(auto& attack : tower->attacks) {
                for(auto& enemy : enemyManager.enemyList) {
                    if(!enemy->isActiveFlag) continue;

                    // std::cerr << "enemy position: " << enemy->position.x << ", " << enemy->position.y << std::endl;
                    if(attack->isInRange(enemy->getBoundingBox(), enemy->rotation, enemy->properties.isCamo, tower->attackBuff)) {
                        enemiesInRange.push_back(enemy.get());
                    }
                }
                
                // Pick one enemy based on the tower's target priority
                // Sadly have to use switch/case here.
                Enemy* targetEnemy = nullptr;
                if(!enemiesInRange.empty()) {
                    switch(tower->targetPriority) {
                        case TargetPriority::First:
                        targetEnemy = enemiesInRange.front();
                        break;
                        case TargetPriority::Last:
                        targetEnemy = enemiesInRange.back();
                        break;
                        case TargetPriority::Close:
                        targetEnemy = *std::min_element(enemiesInRange.begin(), enemiesInRange.end(),
                            [&](Enemy* a, Enemy* b) {
                                return Vector2Distance(a->position, tower->position) < Vector2Distance(b->position, tower->position);
                            });
                        break;
                        case TargetPriority::Strong:
                        targetEnemy = *std::max_element(enemiesInRange.begin(), enemiesInRange.end(),
                        [&](Enemy* a, Enemy* b) {
                            return a->health < b->health; // Compare health
                        });
                        break;
                    }
                }
                
                // update the rotation of the tower to face the target enemy
                if(targetEnemy) {
                    float angle = atan2f(targetEnemy->position.y - tower->position.y, targetEnemy->position.x - tower->position.x);
                    tower->setRotation(angle * (180.0f / PI) + 90.0f); // Convert radians to degrees
                    
                    attack->update(bulletManager, targetEnemy->position, tower->attackBuff, *tower->attackPattern);
                }
            }
        }
    }
}

bool LogicManager::isSpawnTower(const ResourceManager& resourceManager, const TowerManager& towerManager, const MapManager& mapManager) const {
    if(towerManager.putTower == nullptr) {
        // std::cerr << "No tower selected to spawn." << std::endl;
        return false; // No tower selected to spawn
    }

    auto enemyPath = mapManager.currentMap->enemyPath;
    Rectangle towerBoundingBox = towerManager.putTower->getBoundingBox();
    float pathWidth = 25.0f; // Considerable size

    // Checking collision with the map boundaries
    if(!Utils::isPositionInMap({towerBoundingBox.x, towerBoundingBox.y})
    || !Utils::isPositionInMap({towerBoundingBox.x + towerBoundingBox.width, towerBoundingBox.y + towerBoundingBox.height})) {
        // std::cerr << "Cannot put tower outside of the map boundaries." << std::endl;
        
        towerManager.putTower->setActive(false);
        return false; 
    }

    //Checking collision with the path
    for(int x = towerBoundingBox.x; x <= towerBoundingBox.x + towerBoundingBox.width; ++x) {
        for(int y = towerBoundingBox.y; y <= towerBoundingBox.y + towerBoundingBox.height; ++y) {
            Vector2 point = {static_cast<float>(x), static_cast<float>(y)};
            if(mapManager.getCurrentMap().getTowerPointType(point) != Point::Type::None) {
                std::cerr << "Cannot put tower due to path" << std::endl;
                towerManager.putTower->setActive(false);
                return false; // Collision with the path
            }
        }
    }
    // for(const auto& path : enemyPath) {
    //     for(int i = 0; i + 1 < path.size(); ++i) {
    //         if(distancePointLine({towerBoundingBox.x, towerBoundingBox.y}, path[i].position, path[i + 1].position) < pathWidth
    //         || distancePointLine({towerBoundingBox.x + towerBoundingBox.width, towerBoundingBox.y}, path[i].position, path[i + 1].position) < pathWidth
    //         || distancePointLine({towerBoundingBox.x, towerBoundingBox.y + towerBoundingBox.height}, path[i].position, path[i + 1].position) < pathWidth
    //         || distancePointLine({towerBoundingBox.x + towerBoundingBox.width, towerBoundingBox.y + towerBoundingBox.height}, path[i].position, path[i + 1].position) < pathWidth) {
    //             std::cerr << "Cannot put tower due to path" << std::endl;

    //             towerManager.putTower->setActive(false);
    //             return false; 
    //         }
    //     }
    // }
    
    // Checking collision with other towers
    for (const auto& tower : towerManager.towerList) {
        if (tower->isActive() && CheckCollisionRecs(tower->getBoundingBox(), towerBoundingBox)) {
            // std::cerr << "Cannot put tower due to other towers" << std::endl;
            
            towerManager.putTower->setActive(false);
            return false; // Collision with another tower
        }
    }
    
    // Check if the player has enough resources to spawn the tower
    int towerCost = towerManager.putTower->cost;
    if(resourceManager.currentResource.cash < towerCost) {
        // std::cerr << "Current cash: " << resourceManager.currentResource.cash << ", Tower cost: " << towerCost << std::endl;
        // std::cerr << "Not enough resources to spawn tower." << std::endl;
        
        towerManager.putTower->setActive(false);
        return false; // Not enough resources
    }

    towerManager.putTower->setActive(true);
    return true;
}

float LogicManager::distancePointLine(Vector2 point, Vector2 lineStart, Vector2 lineEnd) const {
    Vector2 lineDir = {lineEnd.x - lineStart.x, lineEnd.y - lineStart.y};
    float lineLength = Vector2Length(lineDir);
    if (lineLength == 0.0f) {
        return Vector2Distance(point, lineStart); // If the line is a point, return distance to that point
    }

    lineDir.x /= lineLength; // Normalize the direction vector
    lineDir.y /= lineLength;
    float t = (point.x - lineStart.x) * lineDir.x + (point.y - lineStart.y) * lineDir.y; // Project point onto the line
    t = fmaxf(0.0f, fminf(t, lineLength)); // Clamp t to the segment length
    Vector2 closestPoint = {lineStart.x + t * lineDir.x, lineStart.y + t * lineDir.y}; // Find the closest point on the line segment
    return Vector2Distance(point, closestPoint); // Return the distance from the point to the closest point on the line segment
}

bool LogicManager::spawnTower(ResourceManager& resourceManager, TowerManager& towerManager, const MapManager& mapManager) {
    if(!isSpawnTower(resourceManager, towerManager, mapManager)) {
        return false; 
    }
    
    towerManager.spawnTower(towerManager.putTower->type, towerManager.putTower->position);

    resourceManager.currentResource.cash -= towerManager.putTower->cost;

    towerManager.putTower = nullptr; 

    return true;
}

bool LogicManager::isUpgradeTower(const ResourceManager& resourceManager, const TowerManager& towerManager, UpgradeUnits upgradeUnits) const {
    std::weak_ptr<Tower> tower = towerManager.lastPickedTower;
    auto towerPtr = tower.lock();
    if(!towerPtr) return false; // No tower selected for upgrade

    // Sadly, another switch/case here.
    switch (upgradeUnits) {
        case UpgradeUnits::Top:
            if (towerPtr->upgradeTop->getCost() * towerPtr->upgradeCost <= resourceManager.currentResource.cash 
            && towerPtr->upgradeTop->getName() != "NoUpgrade") {
                return true;
            }
            break;
        case UpgradeUnits::Middle:
            if (towerPtr->upgradeMiddle->getCost() * towerPtr->upgradeCost <= resourceManager.currentResource.cash 
            && towerPtr->upgradeMiddle->getName() != "NoUpgrade") {
                return true;
            }
            break;
        case UpgradeUnits::Bottom:
            if (towerPtr->upgradeBottom->getCost() * towerPtr->upgradeCost <= resourceManager.currentResource.cash 
            && towerPtr->upgradeBottom->getName() != "NoUpgrade") {
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

bool LogicManager::upgradeTower(ResourceManager& resourceManager, TowerManager& towerManager, UpgradeUnits upgradeUnits) {
    std::weak_ptr<Tower> tower = towerManager.lastPickedTower;
    auto towerPtr = tower.lock();
    if(!towerPtr) return false; // No tower selected for upgrade

    // Sadly, another switch/case here.
    switch (upgradeUnits) {
        case UpgradeUnits::Top:
            if (isUpgradeTower(resourceManager, towerManager, UpgradeUnits::Top)) {
                towerPtr->upgradeTop->update(towerPtr->attacks, towerPtr->attackBuff, towerPtr->attackPattern, towerPtr->skill);
                towerPtr->info["nameTop"] = towerPtr->upgradeTop->getName();
                towerPtr->info["descriptionTop"] = towerPtr->upgradeTop->getDescription();
                towerPtr->cost += static_cast<int>(towerPtr->upgradeTop->getCost() * towerPtr->upgradeCost);
                resourceManager.currentResource.cash -= static_cast<int>(towerPtr->upgradeTop->getCost() * towerPtr->upgradeCost);

                towerPtr->upgradeTop = towerPtr->upgradeTop->buy();
                towerPtr->upgradeTop->loadTexture();
                towerPtr->info["upgradeNameTop"] = towerPtr->upgradeTop->getName();
                towerPtr->info["upgradeCostTop"] = std::to_string(static_cast<int>(towerPtr->upgradeTop->getCost() * towerPtr->upgradeCost));
                towerPtr->info["upgradeDescriptionTop"] = towerPtr->upgradeTop->getDescription();

                towerPtr->upgradeTextureHandler.upgradeTopTexture();

                return true;
            }
            break;
        case UpgradeUnits::Middle:
            if (isUpgradeTower(resourceManager, towerManager, UpgradeUnits::Middle)) {
                towerPtr->upgradeMiddle->update(towerPtr->attacks, towerPtr->attackBuff, towerPtr->attackPattern, towerPtr->skill);
                towerPtr->info["nameMiddle"] = towerPtr->upgradeMiddle->getName();
                towerPtr->info["descriptionMiddle"] = towerPtr->upgradeMiddle->getDescription();
                towerPtr->cost += static_cast<int>(towerPtr->upgradeMiddle->getCost() * towerPtr->upgradeCost);
                resourceManager.currentResource.cash -= static_cast<int>(towerPtr->upgradeMiddle->getCost() * towerPtr->upgradeCost);

                towerPtr->upgradeMiddle = towerPtr->upgradeMiddle->buy();
                towerPtr->upgradeMiddle->loadTexture();
                towerPtr->info["upgradeNameMiddle"] = towerPtr->upgradeMiddle->getName();
                towerPtr->info["upgradeCostMiddle"] = std::to_string(static_cast<int>(towerPtr->upgradeMiddle->getCost() * towerPtr->upgradeCost));
                towerPtr->info["upgradeDescriptionMiddle"] = towerPtr->upgradeMiddle->getDescription();

                towerPtr->upgradeTextureHandler.upgradeMiddleTexture();

                return true;
            }
            break;
        case UpgradeUnits::Bottom:
            if (isUpgradeTower(resourceManager, towerManager, UpgradeUnits::Bottom)) {
                towerPtr->upgradeBottom->update(towerPtr->attacks, towerPtr->attackBuff, towerPtr->attackPattern, towerPtr->skill);
                towerPtr->info["nameBottom"] = towerPtr->upgradeBottom->getName();
                towerPtr->info["descriptionBottom"] = towerPtr->upgradeBottom->getDescription();
                towerPtr->cost += static_cast<int>(towerPtr->upgradeBottom->getCost() * towerPtr->upgradeCost);
                resourceManager.currentResource.cash -= static_cast<int>(towerPtr->upgradeBottom->getCost() * towerPtr->upgradeCost);

                towerPtr->upgradeBottom = towerPtr->upgradeBottom->buy();
                towerPtr->upgradeBottom->loadTexture();
                towerPtr->info["upgradeNameBottom"] = towerPtr->upgradeBottom->getName();
                towerPtr->info["upgradeCostBottom"] = std::to_string(static_cast<int>(towerPtr->upgradeBottom->getCost() * towerPtr->upgradeCost));
                towerPtr->info["upgradeDescriptionBottom"] = towerPtr->upgradeBottom->getDescription();

                towerPtr->upgradeTextureHandler.upgradeBottomTexture();

                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

bool LogicManager::activateSkillTower(TowerManager& towerManager, EnemyManager& enemyManager) {
    std::weak_ptr<Tower> tower = towerManager.lastPickedTower;
    auto towerPtr = tower.lock();
    if(!towerPtr) return false; // No tower selected for skill activation

    if(towerPtr->skill && towerPtr->skill->canActivateSkill()) {
        // Activate the skill
        towerPtr->skill->activateSkill(towerPtr, enemyManager.enemyList, towerManager.towerList);
        // std::cerr << "Activated skill: " << tower->skill->name << std::endl;
        return true;
    }

    return false;
}

void LogicManager::sellTower(ResourceManager& resourceManager, TowerManager& towerManager) {
    int sellValue = towerManager.sellTower();
    if (sellValue > 0) {
        MySound sellSound("Cash");
        sellSound.start();
        resourceManager.currentResource.cash += sellValue;
    }
}

bool LogicManager::isPlayingRound(ModeManager& modeManager, EnemyManager& enemyManager) const {
    // Check if the game is in a state where a round can be played
    return !modeManager.canPlayNextRound(enemyManager.enemyList.empty());
}

bool LogicManager::playRound(ResourceManager& resourceManager, ModeManager& modeManager, EnemyManager& enemyManager, BulletManager& bulletManager, MapManager& mapManager) {
    // set the roundNumber being played
    int roundNumber = resourceManager.currentResource.currentRound;
    modeManager.playRound(roundNumber);

    std::vector<std::pair<BloonType, BloonProperties>> enemies = modeManager.getEnemies();
    // if(!enemies.empty()) std::cerr << "Playing round " << roundNumber << " with " << enemies.size() << " enemies." << std::endl;
    for(const auto& [type, properties] : enemies) {
        // Spawn each enemy with the given type and properties
        auto [position, pathIdx] = mapManager.getCurrentMap().getPositionAndPathIdx(type);
        enemyManager.spawnEnemy(type, properties, mapManager.getCurrentMap().getCurrentPoint(0, pathIdx), pathIdx);
    }

    // end round logic
    bool isSave = false;
    if (!isPlayingRound(modeManager, enemyManager)) {
        // reward cash
        int reward = modeManager.getRoundReward();
        resourceManager.currentResource.cash += reward;
        isSave = (reward != 0);

        // auto play next round
        if(autoPlayRound) {
            playNextRound(modeManager, enemyManager, bulletManager, resourceManager);
            return true;
        }
    }

    return isSave;
}

void LogicManager::playNextRound(ModeManager& modeManager, EnemyManager& enemyManager, BulletManager& bulletManager, ResourceManager& resourceManager) {
    if(isPlayingRound(modeManager, enemyManager)) return;

    bulletManager.bulletList.clear(); 

    resourceManager.currentResource.currentRound++;
    std::cerr << "Playing next round: " << resourceManager.currentResource.currentRound << std::endl;
}

void LogicManager::setAutoPlay(ModeManager& modeManager, bool autoPlay) {
    autoPlayRound = modeManager.setAutoPlay(autoPlay);
}