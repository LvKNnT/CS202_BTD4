#include "Black.h"
#include <fstream>

Black::Black(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Black, 1, 180, 1, 11) {
    /**
     * Health = 1
     * Speed = 180
     * Reward = 1
     * Lives lost = 11
     */

    // Variable initialization that can't use initializer list
    tag = "Black";
}  

std::unique_ptr<Enemy> Black::clone() const {
    return std::make_unique<Black>(*this);
}

void Black::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = properties.getPath() + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);
    texture = Game::Instance().getTextureManager().getTexture(fullTag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);

    tag = fullTag;
}

bool Black::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Black bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Black::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Black::draw() const {
    // Check if the bloon is active before drawing
    if (!isActiveFlag) {
        return; 
    }
    
    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x - size.x / 2.0f),
        roundf(position.y - size.y / 2.0f)
    };    

    DrawTextureV(texture, draw_position, WHITE); // Draw the bloon texture at its position
}

Rectangle Black::getBoundingBox() const {
    return Rectangle{
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    };
}

bool Black::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Black::setActive(bool active) {
    // Set the active state of the Black bloon
    isActiveFlag = active;
}

void Black::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Black::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Black::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Black bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}