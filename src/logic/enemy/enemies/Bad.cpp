#include "Bad.h"
#include <fstream>

Bad::Bad(Vector2 position) 
    : Enemy(position, {0, 0}, 0.0f, BloonType::Bad, 20000, 18, 1, 55760) {
    /**
     * Health = 20000
     * Speed = 18
     * Reward = 1
     * Lives lost = 55760
     */

    // Variable initialization that cant use initializer list
    tag = "BAD";
}
Bad::~Bad() {
    // Cleanup if necessary
}

std::unique_ptr<Enemy> Bad::clone() const {
    return std::make_unique<Bad>(*this);
}

void Bad::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = "../assets/enemy/MOAB Class Bloons/" + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);
    texture = Game::Instance().getTextureManager().getTexture(fullTag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);

    tag = fullTag;
}

bool Bad::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Bad bloon popped!" << std::endl;
        flog.close();
        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();
    
    return true;
}

void Bad::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Bad::draw() const {
    // Check if the bloon is active before drawing
    if (!isActiveFlag) {
        return; 
    }

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(texture, 
                   {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the Bad bloon texture with the specified position and rotation
}

Rectangle Bad::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2, position.y - size.y / 2, size.x, size.y};
}

bool Bad::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Bad::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}
    
void Bad::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the Bad bloon
    return;
}

void Bad::setModifies(const EnemyModifies& modifies) {
    // Set the enemy modifiers for the Bad bloon
    speed = static_cast<int>(speed * modifies.speed);
    health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Bad::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Bad bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}