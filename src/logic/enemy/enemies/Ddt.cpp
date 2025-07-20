#include "Ddt.h"
#include <fstream>

Ddt::Ddt(Vector2 position) 
    : Enemy(position, {0, 0}, 0.0f, BloonType::Ddt, 400, 264, 1, 816) {
    /**
     * Health = 400
     * Speed = 264
     * Reward = 1
     * Lives lost = 816
     */

    // Variable initialization that cant use initializer list
    tag = "DdtBloon";
}
Ddt::~Ddt() {
    // Cleanup if necessary
}

std::unique_ptr<Enemy> Ddt::clone() const {
    return std::make_unique<Ddt>(*this);
}

void Ddt::loadTexture() {
    // Load the texture
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/enemy/MOAB Class Bloons/BTD6DDT.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

bool Ddt::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Ddt bloon popped!" << std::endl;
        flog.close();
        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();
    
    return true;
}

void Ddt::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Ddt::draw() const {
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
                   WHITE); // Draw the Ddt bloon texture with the specified position and rotation
}

Rectangle Ddt::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2, position.y - size.y / 2, size.x, size.y};
}

bool Ddt::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Ddt::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}
    
void Ddt::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the Ddt bloon
    return;
}

void Ddt::setModifies(const EnemyModifies& modifies) {
    // Set the enemy modifiers for the Ddt bloon
    speed = static_cast<int>(speed * modifies.speed);
    health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}