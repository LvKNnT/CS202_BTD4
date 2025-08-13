#include "Blue.h"
#include <fstream>

Blue::Blue(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Blue, 1, 140, 1, 2) {
    /**
     * Health = 1
     * Speed = 140
     * Reward = 1
     * Lives lost = 2
     */

    // Variable initialization that can't use initializer list
    tag = "Blue";
}  

std::unique_ptr<Enemy> Blue::clone() const {
    return std::make_unique<Blue>(*this);
}

void Blue::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = properties.getPath() + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Blue::hit(int damage) {
    MySound popSound("NormalBloon");
    popSound.start();

    health -= damage;
    health -= debuff.bonusOnHitDamage; // Apply bonus damage from debuffs

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Blue bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Blue::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Blue::draw() const {
    // Check if the bloon is active before drawing
    if (!isActiveFlag) {
        return; 
    }
    
    // Rounded draw position
    Vector2 draw_position = {
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f
    };

    DrawTextureV(Game::Instance().getTextureManager().getTexture(tag), draw_position, WHITE); // Draw the bloon texture at its position
}

Rectangle Blue::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Blue::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void Blue::setActive(bool active) {
    // Set the active state of the Blue bloon
    isActiveFlag = active;
}

void Blue::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a normal bloon
    debuff += normalDebuff; 
}

void Blue::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Blue::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Blue::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Blue bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}