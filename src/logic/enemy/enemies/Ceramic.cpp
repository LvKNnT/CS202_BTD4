#include "Ceramic.h"
#include <fstream>

Ceramic::Ceramic(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Ceramic, 10, 250, 1, 104) {
    /**
     * Health = 10
     * Speed = 250
     * Reward = 1
     * Lives lost = 104
     */

    // Variable initialization that can't use initializer list
    tag = "CeramicBloon";
}  

std::unique_ptr<Enemy> Ceramic::clone() const {
    return std::make_unique<Ceramic>(*this);
}

void Ceramic::loadTexture() {
    // Load the texture
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/enemy/Normal Bloons/default/BTD6Ceramic.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

bool Ceramic::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Ceramic bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Ceramic::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Bloon reached the end of the track!" << std::endl;
    flog.close();
}

void Ceramic::draw() const {
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

Rectangle Ceramic::getBoundingBox() const {
    return Rectangle{
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    };
}

bool Ceramic::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Ceramic::setActive(bool active) {
    // Set the active state of the Ceramic bloon
    isActiveFlag = active;
}

void Ceramic::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Ceramic::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}