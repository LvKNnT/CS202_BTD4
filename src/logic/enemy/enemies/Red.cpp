#include "Red.h"
#include <fstream>

Red::Red(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Red, 1, 100, 1, 1) { 
    /**
     * Health = 1
     * Speed = 100
     * Reward = 1
     * Live lost = 1
     *  */ 

    // Variable initialization that cant use initializer list
    tag = "Red";
}

std::unique_ptr<Enemy> Red::clone() const {
    return std::make_unique<Red>(*this);
}

void Red::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = properties.getPath() + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Red::hit(int damage) {
    MySound popSound("NormalBloon");
    popSound.start();

    health -= damage;
    health -= debuff.bonusOnHitDamage; // Apply bonus damage from debuffs
    
    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Red bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Red::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Red::draw() const {
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

Rectangle Red::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Red::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void Red::setActive(bool active) {
    isActiveFlag = active;
}

void Red::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Red::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a normal bloon
    debuff += normalDebuff; 
}

void Red::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Red::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Red bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}