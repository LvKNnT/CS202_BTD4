#include "BulletSpawner.h"

// Headers for bullet types
#include "bullets/Dart.h"
// #include "bullets/Bomb.h"
// #include "bullets/Tack.h"
// #include "bullets/Ice.h"
// #include "bullets/MagicBall.h"
// #include "bullets/Shuriken.h"

BulletSpawner::BulletSpawner() {
    /**
     * Technical issue:
     * Currently can't use constructor to initialize bullet templates
     * because the texture manager is not ready yet.
     */

    // Initialize bullet templates
    init();
}

BulletSpawner::BulletSpawner(const BulletSpawner& other) {
    if (this != &other) {
        bulletTemplates.clear();
        for (const auto& pair : other.bulletTemplates) {
            bulletTemplates[pair.first] = pair.second->clone();
        }
    } else {
        // should not be here
    }
}

BulletSpawner& BulletSpawner::operator=(const BulletSpawner& other) {
    if (this != &other) {
        bulletTemplates.clear();
        for (const auto& pair : other.bulletTemplates) {
            bulletTemplates[pair.first] = pair.second->clone();
        }
    } else {
        // should not be here
    }
    return *this;
}

std::unique_ptr<BulletSpawner> BulletSpawner::clone() const {
    return std::make_unique<BulletSpawner>(*this);
}

void BulletSpawner::init() {
    // Load bullet templates
    bulletTemplates[BulletType::Dart] = std::make_unique<Dart>();
    // bulletTemplates[BulletType::Bomb] = std::make_unique<Bomb>();
    // bulletTemplates[BulletType::Tack] = std::make_unique<Tack>();
    // bulletTemplates[BulletType::Ice] = std::make_unique<Ice>();
    // bulletTemplates[BulletType::MagicBall] = std::make_unique<MagicBall>();
    // bulletTemplates[BulletType::Shuriken] = std::make_unique<Shuriken>();
}

std::unique_ptr<Bullet> BulletSpawner::getBullet(BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, int towerId) {
    auto it = bulletTemplates.find(type);
    if (it != bulletTemplates.end()) {
        it->second->loadTexture(); 
        
        std::unique_ptr<Bullet> bullet = it->second->clone();
        bullet->position = position;
        bullet->size = size;
        bullet->rotation = rotation;
        bullet->damage = damage;
        bullet->speed = speed;
        bullet->pierce = pierce;
        bullet->lifeSpan = lifeSpan;
        bullet->towerId = towerId; 

        return bullet;
    }
    return nullptr; // Return nullptr if the bullet type is not found
}