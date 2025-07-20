#include "Rainbow.h"
#include <fstream>

Rainbow::Rainbow(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Rainbow, 1, 220, 1, 47) {
    /**
     * Health = 1
     * Speed = 220
     * Reward = 1
     * Lives lost = 47
     */

    // Variable initialization that can't use initializer list
    tag = "RainbowBloon";
}  

std::unique_ptr<Enemy> Rainbow::clone() const {
    return std::make_unique<Rainbow>(*this);
}

void Rainbow::loadTexture() {
    // Load the texture
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/enemy/Normal Bloons/default/BTD6Rainbow.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

bool Rainbow::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Rainbow bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Rainbow::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Rainbow::draw() const {
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

Rectangle Rainbow::getBoundingBox() const {
    return Rectangle{
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    };
}

bool Rainbow::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Rainbow::setActive(bool active) {
    // Set the active state of the Rainbow bloon
    isActiveFlag = active;
}

void Rainbow::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Rainbow::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}