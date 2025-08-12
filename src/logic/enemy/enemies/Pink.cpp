#include "Pink.h"
#include <fstream>

Pink::Pink(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Pink, 1, 350, 1, 5) {
    /**
     * Health = 1
     * Speed = 350
     * Reward = 1
     * Lives lost = 5
     */

    // Variable initialization that can't use initializer list
    tag = "Pink";
}  

std::unique_ptr<Enemy> Pink::clone() const {
    return std::make_unique<Pink>(*this);
}

void Pink::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = properties.getPath() + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Pink::hit(int damage) {
    MySound popSound("NormalBloon");
    popSound.start();

    health -= damage;
    health -= debuff.bonusDamage; // Apply bonus damage from debuffs

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Pink bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Pink::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Pink::draw() const {
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

Rectangle Pink::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Pink::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void Pink::setActive(bool active) {
    // Set the active state of the Pink bloon
    isActiveFlag = active;
}

void Pink::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Pink::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a normal bloon
    debuff += normalDebuff; 
}

void Pink::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Pink::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Pink bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}