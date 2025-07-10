#include "LogicManager.h"

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
    int speed = enemy.speed;

    Vector2 nextPoint = map.getNextPoint(trackIndex);
    Vector2 direction = {nextPoint.x - position.x, nextPoint.y - position.y};
    float distance = Vector2Distance(position, nextPoint);

    // Continously move the enemy until it reaches the next point
    while (elapsedTime > 0.0f || map.isLastPoint(trackIndex)) {
        nextPoint = map.getNextPoint(trackIndex);
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

        if (map.isLastPoint(trackIndex)) {
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
    enemy.isActiveFlag = map.getPointType(trackIndex) != Point::Type::Invisible; // Check if the enemy is still active based on the point type

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

void LogicManager::updateBulletsHitEnemies(BulletManager& bulletManager, EnemyManager& enemyManager, MapManager& mapManager) {
    for (auto enemyIt = enemyManager.enemyList.begin(); enemyIt != enemyManager.enemyList.end(); ) {
        std::unique_ptr<Enemy>& enemy = *enemyIt;
        bool isEnemyRemoved = false;

        for (auto bulletIt = bulletManager.bulletList.begin(); bulletIt != bulletManager.bulletList.end(); ) {
            if (checkCollision(**bulletIt, *enemy)) {
                std::vector<std::unique_ptr<Enemy>> children = getChildrenEnemies(enemyManager, *enemy, (*bulletIt)->damage);

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

std::vector<std::unique_ptr<Enemy>> LogicManager::getChildrenEnemies(EnemyManager& enemyManager, Enemy& enemy, int damage) {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << enemy.tag << " hit with damage: " << damage << std::endl;
    flog.close();
    
    if(enemy.hit(damage)) {
        return {};
    }

    std::vector<std::unique_ptr<Enemy>> childrenEnemies;
    childrenEnemies = enemyManager.spawnChildrenEnemies(enemy.type, enemy.position);

    int remainingHealth = -enemy.health; // Get the remaining health after damage
    std::vector<std::unique_ptr<Enemy> > finalChildrenEnemies;

    for(auto& child : childrenEnemies) {
        if(remainingHealth > 0) {
            auto subChildren = getChildrenEnemies(enemyManager, *child, remainingHealth);

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
        else {
            // If no remaining health, just add the child
            finalChildrenEnemies.push_back(std::move(child));
        }
    }

    for(auto& child : finalChildrenEnemies) {
        child->trackIndex = enemy.trackIndex; // Set the track index to the same as the parent enemy
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

        corners[0] = {rect.x - halfWidth, rect.y - halfHeight}; // Top-left
        corners[1] = {rect.x + halfWidth, rect.y - halfHeight}; // Top-right
        corners[2] = {rect.x + halfWidth, rect.y + halfHeight}; // Bottom-right
        corners[3] = {rect.x - halfWidth, rect.y + halfHeight}; // Bottom-left

        // Rotate corners around the center of the rectangle
        for (int i = 0; i < 4; ++i) {
            float x = corners[i].x - rect.x;
            float y = corners[i].y - rect.y;
            
            corners[i].x = rect.x + x * cosTheta - y * sinTheta;
            corners[i].y = rect.y + x * sinTheta + y * cosTheta;
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
                    if(attack->isInRange(enemy->position)) {
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

float LogicManager::Vector2Distance(Vector2& a, Vector2& b) const {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}