#include "BulletSpawner.h"

#include <iostream>

// Headers for bullet types
#include "bullets/Dart.h"
#include "bullets/TracingDart.h"
#include "bullets/SpikeOPultBullet.h"
#include "bullets/JuggernautBullet.h"
#include "bullets/UltraJuggernautBullet.h"
#include "bullets/Arrow.h"
#include "bullets/ArrowCrit.h"
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
    bulletTemplates[BulletType::TracingDart] = std::make_unique<TracingDart>();
    bulletTemplates[BulletType::SpikeOPult] = std::make_unique<SpikeOPultBullet>();
    bulletTemplates[BulletType::Juggernaut] = std::make_unique<JuggernautBullet>();
    bulletTemplates[BulletType::UltraJuggernaut] = std::make_unique<UltraJuggernautBullet>();
    bulletTemplates[BulletType::Arrow] = std::make_unique<Arrow>();
    bulletTemplates[BulletType::ArrowCrit] = std::make_unique<ArrowCrit>();
    // bulletTemplates[BulletType::Tack] = std::make_unique<Tack>();
    // bulletTemplates[BulletType::Ice] = std::make_unique<Ice>();
    // bulletTemplates[BulletType::MagicBall] = std::make_unique<MagicBall>();
    // bulletTemplates[BulletType::Shuriken] = std::make_unique<Shuriken>();
}

std::unique_ptr<Bullet> BulletSpawner::getBullet(BulletType type, Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties& properties, BloonDebuff& normalDebuff, BloonDebuff& moabDebuff, AttackBuff& attackBuff, int towerId) {
    auto it = bulletTemplates.find(type);
    if (it != bulletTemplates.end()) {
        it->second->loadTexture(); 
        
        std::unique_ptr<Bullet> bullet = it->second->clone();
        bullet->init(position, size, rotation, damage, speed, pierce, lifeSpan, properties, normalDebuff, moabDebuff, attackBuff, towerId);

        return bullet;
    }

    std::cerr << "Bullet type not found: " << static_cast<int>(type) << std::endl;
    return nullptr; // Return nullptr if the bullet type is not found
}