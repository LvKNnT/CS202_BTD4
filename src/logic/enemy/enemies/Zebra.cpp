#include "Zebra.h"
#include <fstream>

Zebra::Zebra(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Zebra, 1, 180, 1, 23) {
    /**
     * Health = 1
     * Speed = 180
     * Reward = 1
     * Lives lost = 23
     */

    // Variable initialization that can't use initializer list
    tag = "Zebra";
}  

std::unique_ptr<Enemy> Zebra::clone() const {
    return std::make_unique<Zebra>(*this);
}

void Zebra::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = properties.getPath() + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Zebra::hit(int damage) {
    MySound popSound("NormalBloon");
    popSound.start();
    
    health -= damage;
    health -= debuff.bonusOnHitDamage; // Apply bonus damage from debuffs

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Zebra bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Zebra::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Zebra::draw() const {
    // Check if the bloon is active before drawing
    if (!isActiveFlag) {
        return; 
    }
    
    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x - size.x / 2.0f),
        roundf(position.y - size.y / 2.0f)
    };    

    DrawTextureV(Game::Instance().getTextureManager().getTexture(tag), draw_position, WHITE); // Draw the bloon texture at its position
}

Rectangle Zebra::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Zebra::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void Zebra::setActive(bool active) {
    // Set the active state of the Zebra bloon
    isActiveFlag = active;
}

void Zebra::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Zebra::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a normal bloon
    debuff += normalDebuff; 
}

void Zebra::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Zebra::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Zebra bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}