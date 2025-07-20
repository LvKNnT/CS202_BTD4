#include "LogicManager.h"

#include "raymath.h"

#include <cfloat>
#include <algorithm>
#include <fstream>

void LogicManager::updateEnemies(EnemyManager& enemyManager, MapManager& mapManager) {
    for (auto it = enemyManager.enemyList.begin(); it != enemyManager.enemyList.end(); ) {
        int result = runEnemy(**it, mapManager.getCurrentMap());
        
        if (result == -1) {
            // Enemy reached the end — remove and destroy it
            it = enemyManager.enemyList.erase(it);  // erase returns the next iterator
            continue;  // Skip the increment, already moved to next
        }
        ++it;
    }
}

// Logic to move the enemy along the path
int LogicManager::runEnemy(Enemy& enemy, const Map& map) {
    float elapsedTime = GetFrameTime();
    Vector2 position = enemy.position;
    int trackIndex = enemy.trackIndex;
    int pathIndex = enemy.pathIndex; 
    int speed = enemy.speed;

    Vector2 nextPoint = map.getNextPoint(trackIndex, pathIndex);
    Vector2 direction = {nextPoint.x - position.x, nextPoint.y - position.y};
    float distance = Vector2Distance(position, nextPoint);

    // Continously move the enemy until it reaches the next point
    while (elapsedTime > 0.0f || map.isLastPoint(trackIndex, pathIndex)) {
        nextPoint = map.getNextPoint(trackIndex, pathIndex);
        direction = {nextPoint.x - position.x, nextPoint.y - position.y};
        distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

        // Move the enemy towards the next point
        if (speed * elapsedTime < distance) {
            position.x += direction.x / distance * speed * elapsedTime;
            position.y += direction.y / distance * speed * elapsedTime;
            elapsedTime = 0.0f; // Use all the rest of the time
        } else {
            position = nextPoint; // Move to the next point
            trackIndex++; // Move to the next point in the path
            elapsedTime -= distance / speed; // Reduce the elapsed time by the time taken to reach the next point
        }

        if (map.isLastPoint(trackIndex, pathIndex)) {
            // Before returning, update the enemy's position and track index
            enemy.position = position;
            enemy.trackIndex = trackIndex; // Move to the next point in the path

            enemy.die(); // Call the die method to handle reaching the end of the path

            return -1; // Enemy has reached the end of the path
        }
    }

    // Before returning, update the enemy's position and track index
    enemy.position = position; 
    enemy.trackIndex = trackIndex; 
    enemy.setRotation(atan2f(direction.y, direction.x) * (180.0f / PI)); // Set the rotation based on the direction
    enemy.isActiveFlag = map.getPointType(trackIndex, pathIndex) != Point::Type::Invisible; // Check if the enemy is still active based on the point type

    // If the enemy has not reached the end of the path, return 0
    return 0;
}

void LogicManager::updateBullets(BulletManager& bulletManager, MapManager& mapManager) {
    for(auto it = bulletManager.bulletList.begin(); it != bulletManager.bulletList.end(); ) {
        // Check if the bullet is still on the map
        int result = runBullet(**it, mapManager.getCurrentMap());

        if (result == -1) {
            // Bullet has reached the end of its life — remove and destroy it
            it = bulletManager.bulletList.erase(it);  // erase returns the next iterator
            continue;  // Skip the increment, already moved to next
        }
        
        // Update the life span of the bullet
        (*it)->lifeSpan -= GetFrameTime();
        
        if ((*it)->lifeSpan <= 0) {
            // Bullet has reached the end of its life span — remove and destroy it
            it = bulletManager.bulletList.erase(it);  // erase returns the next iterator
            continue;  // Skip the increment, already moved to next
        }

        ++it;
    }
}

int LogicManager::runBullet(Bullet& bullet, const Map& map) {
    float elapsedTime = GetFrameTime();
    Vector2 position = bullet.position;
    float rotation = bullet.rotation;
    int speed = bullet.speed;

    Vector2 direction = {cosf(rotation * (PI / 180.0f)), sinf(rotation * (PI / 180.0f))};
    position.x += direction.x * speed * elapsedTime;
    position.y += direction.y * speed * elapsedTime;

    // Update the bullet's position
    bullet.position = position;

    // Check if the bullet is still within the bounds of the map
    if (!map.isWithinBounds(position)) {
        bullet.die(); // Call the die method to handle the end of the bullet's life
        return -1; // Bullet has reached the end of its life
    }

    // If the bullet is still active, return 0
    return 0;
}

void LogicManager::updateBulletsHitEnemies(BulletManager& bulletManager, EnemyManager& enemyManager, TowerManager& towerManager, MapManager& mapManager) {
    for (auto enemyIt = enemyManager.enemyList.begin(); enemyIt != enemyManager.enemyList.end(); ) {
        std::unique_ptr<Enemy>& enemy = *enemyIt;
        bool isEnemyRemoved = false;

        for (auto bulletIt = bulletManager.bulletList.begin(); bulletIt != bulletManager.bulletList.end(); ) {
            if (checkCollision(**bulletIt, *enemy)) {
                int popCount = 0;
                std::vector<std::unique_ptr<Enemy>> children;
                children = getChildrenEnemies(enemyManager, *enemy, (*bulletIt)->damage, popCount);

                // Add the pop count to the original tower
                for (auto& tower : towerManager.towerList) {
                    if(tower->towerId == (*bulletIt)->towerId) {
                        tower->popCount += popCount; 
                    }
                }

                // Every collision costs bullet damage
                if(enemy->health <= 0) {
                    enemyIt = enemyManager.enemyList.erase(enemyIt); // Remove the current enemy
                    isEnemyRemoved = true; // Mark that the enemy was removed
                }
                enemyManager.enemyList.insert(enemyIt, 
                    std::make_move_iterator(children.begin()), 
                    std::make_move_iterator(children.end()));

                // Every collision cost 1 pierce
                if((*bulletIt)->hit(1)) {
                    bulletIt = bulletManager.bulletList.erase(bulletIt);
                    continue;
                }
            }
            ++bulletIt;
        }
        
        if(!isEnemyRemoved) {
            ++enemyIt;
        }
    }
}

std::vector<std::unique_ptr<Enemy>> LogicManager::getChildrenEnemies(EnemyManager& enemyManager, Enemy& enemy, int damage, int& popCount) {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << enemy.tag << " hit with damage: " << damage << std::endl;
    flog.close();
    
    if(enemy.hit(damage)) {
        popCount += damage;
        return {};
    }

    std::vector<std::unique_ptr<Enemy>> childrenEnemies;
    childrenEnemies = enemyManager.spawnChildrenEnemies(enemy.type, enemy.position);
    
    int remainingHealth = -enemy.health; // Get the remaining health after damage
    int finalPopCount = damage - remainingHealth; // Calculate the pop count`
    popCount += finalPopCount;
    std::vector<std::unique_ptr<Enemy> > finalChildrenEnemies;

    for(auto& child : childrenEnemies) {
        std::vector<std::unique_ptr<Enemy> > subChildren = getChildrenEnemies(enemyManager, *child, remainingHealth, popCount);

        if(!subChildren.empty()) {
            // If there are sub-children, add them to the final list
            for(auto& subChild : subChildren) {
                finalChildrenEnemies.push_back(std::move(subChild));
            }
        } else {
            // Skip adding Red bloon as it has no sub-children
            if(child->type == BloonType::Red) {
                continue;
            }

            // If no sub-children, just add the child
            finalChildrenEnemies.push_back(std::move(child));
            }
    }

    for(auto& child : finalChildrenEnemies) {
        child->trackIndex = enemy.trackIndex; // Set the track index to the same as the parent enemy
        child->pathIndex = enemy.pathIndex; // Set the path index to the same as the parent enemy
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
                    // std::cerr << "enemy position: " << enemy->position.x << ", " << enemy->position.y << std::endl;
                    if(attack->isInRange(enemy->getBoundingBox(), enemy->rotation)) {
                        enemiesInRange.push_back(enemy.get());
                    }
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

                for(auto& attack : tower->attacks) {
                    // Update the attack with the target position
                    attack->update(bulletManager, targetEnemy->position);
                }
            }
        }
    }
}

bool LogicManager::isPutTower(const TowerManager& towerManager, const MapManager& mapManager, TowerType type, Vector2 position) const {
    auto enemyPath = mapManager.currentMap->enemyPath;
    Rectangle towerBoundingBox = towerManager.towerSpawner->getBoundingBox(type, position);
    float pathWidth = 50.0f; // Considerable size

    // Checking collision
    for(const auto& path : enemyPath) {
        for(int i = 0; i + 1 < path.size(); ++i) {
            if(distancePointLine({towerBoundingBox.x, towerBoundingBox.y}, path[i].position, path[i + 1].position) < pathWidth
            || distancePointLine({towerBoundingBox.x + towerBoundingBox.width, towerBoundingBox.y}, path[i].position, path[i + 1].position) < pathWidth
            || distancePointLine({towerBoundingBox.x, towerBoundingBox.y + towerBoundingBox.height}, path[i].position, path[i + 1].position) < pathWidth
            || distancePointLine({towerBoundingBox.x + towerBoundingBox.width, towerBoundingBox.y + towerBoundingBox.height}, path[i].position, path[i + 1].position) < pathWidth) {
                return false; // Tower is too far from the path
            }
        }
    }
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
