#include "Bfb.h"
#include <fstream>

Bfb::Bfb(Vector2 position) 
    : Enemy(position, {0, 0}, 0.0f, BloonType::Bfb, 700, 25, 1, 3164) {
    /**
     * Health = 700
     * Speed = 25
     * Reward = 1
     * Lives lost = 3164
     */

    // Variable initialization that cant use initializer list
    tag = "BFB";
}
Bfb::~Bfb() {
    // Cleanup if necessary
}

std::unique_ptr<Enemy> Bfb::clone() const {
    return std::make_unique<Bfb>(*this);
}

void Bfb::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = "../assets/enemy/MOAB Class Bloons/" + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Bfb::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Bfb bloon popped!" << std::endl;
        flog.close();
        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();
    
    return true;
}

void Bfb::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Bfb::draw() const {
    // Check if the bloon is active before drawing
    if (!isActiveFlag) {
        return; 
    }

    // Rounded draw position
    Vector2 draw_position = {
        roundf(position.x),
        roundf(position.y)
    };    

    DrawTexturePro(Game::Instance().getTextureManager().getTexture(tag), 
                   {0, 0, size.x, size.y},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the Bfb bloon texture with the specified position and rotation
}

Rectangle Bfb::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Bfb::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Bfb::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}

void Bfb::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a MOAB class
    debuff += moabDebuff;
}
    
void Bfb::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the Bfb bloon
    return;
}

void Bfb::setModifies(const EnemyModifies& modifies) {
    // Set the enemy modifiers for the Bfb bloon
    speed = static_cast<int>(speed * modifies.speed);
    health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Bfb::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Bfb bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}