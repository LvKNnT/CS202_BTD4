#include "Zomg.h"
#include <fstream>

Zomg::Zomg(Vector2 position) 
    : Enemy(position, {0, 0}, 0.0f, BloonType::Zomg, 4000, 18, 1, 16656) {
    /**
     * Health = 4000
     * Speed = 18
     * Reward = 1
     * Lives lost = 16656
     */

    // Variable initialization that cant use initializer list
    tag = "ZomgBloon";
}
Zomg::~Zomg() {
    // Cleanup if necessary
}

std::unique_ptr<Enemy> Zomg::clone() const {
    return std::make_unique<Zomg>(*this);
}

void Zomg::loadTexture() {
    // Load the texture
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/enemy/MOAB Class Bloons/BTD6ZOMG.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

bool Zomg::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Zomg bloon popped!" << std::endl;
        flog.close();
        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();
    
    return true;
}

void Zomg::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Bloon reached the end of the track!" << std::endl;
    flog.close();
}

void Zomg::draw() const {
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
                   WHITE); // Draw the Zomg bloon texture with the specified position and rotation
}

Rectangle Zomg::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2, position.y - size.y / 2, size.x, size.y};
}

bool Zomg::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Zomg::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}
    
void Zomg::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the Zomg bloon
    return;
}

void Zomg::setModifies(const EnemyModifies& modifies) {
    // Set the enemy modifiers for the Zomg bloon
    speed = static_cast<int>(speed * modifies.speed);
    health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}