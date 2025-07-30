#include "BulletManager.h"
#include <iostream>
#include <filesystem>

BulletManager::BulletManager() {
    // Initialize unique_ptr
    bulletSpawner = std::make_unique<BulletSpawner>();
}

BulletManager::BulletManager(const BulletManager& other) {
    if (this != &other) {
        bulletSpawner = other.bulletSpawner->clone();

        bulletList.clear();
        for (const std::unique_ptr<Bullet>& bullet : other.bulletList) {
            bulletList.push_back(bullet->clone());
        }
    } 
    else {
        // should not be here
    }
}

BulletManager& BulletManager::operator=(const BulletManager& other) {
    if (this != &other) {
        bulletSpawner = other.bulletSpawner->clone();

        bulletList.clear();
        for (const std::unique_ptr<Bullet>& bullet : other.bulletList) {
            bulletList.push_back(bullet->clone());
        }
    } else {
        // should not be here
    }
    return *this;
}

void BulletManager::spawnBullet(BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff& attackBuff, int towerId) {
    std::unique_ptr<Bullet> bullet = bulletSpawner->getBullet(type, position, size, rotation, damage, speed, pierce, lifeSpan, properties, attackBuff, towerId);
    
    if (bullet) {
        bulletList.push_back(std::move(bullet));
    } else {
        std::cerr << "Failed to spawn bullet of type: " << static_cast<int>(type) << std::endl;
    }
}

void BulletManager::spawnChildBullet(std::unique_ptr<Bullet> bullet) {
    if (bullet) {
        bulletList.push_back(std::move(bullet));
    } else {
        std::cerr << "Failed to spawn child bullet!" << std::endl;
    }
}

void BulletManager::drawBullets() const {
    for (const auto& bullet : bulletList) {
        if(bullet) {
            bullet->draw();
        } else {
            std::cerr << "Bullet is null!" << std::endl;
        }
    }
}

void BulletManager::unLoad() {
    for (auto& bullet : bulletList) {
        if (bullet) {
            bullet->unLoad(); // Unload the bullet resources
        } else {
            std::cerr << "Bullet is null during unload!" << std::endl;
        }
    }
    bulletList.clear(); // Clear the list after unloading
}