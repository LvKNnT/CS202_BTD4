#include "White.h"
#include <fstream>

White::White(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::White, 1, 200, 1, 11) {
    /**
     * Health = 1
     * Speed = 200
     * Reward = 1
     * Lives lost = 11
     */

    // Variable initialization that can't use initializer list
    tag = "White";
}  

std::unique_ptr<Enemy> White::clone() const {
    return std::make_unique<White>(*this);
}

void White::loadTexture() {
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

bool White::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "White bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void White::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void White::draw() const {
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

Rectangle White::getBoundingBox() const {
    return Rectangle{
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    };
}

bool White::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void White::setActive(bool active) {
    // Set the active state of the White bloon
    isActiveFlag = active;
}

void White::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void White::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void White::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the White bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}