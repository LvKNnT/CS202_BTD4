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
    tag = "ZOMG";
}
Zomg::~Zomg() {
    // Cleanup if necessary
}

std::unique_ptr<Enemy> Zomg::clone() const {
    return std::make_unique<Zomg>(*this);
}

void Zomg::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = "../assets/enemy/MOAB Class Bloons/" + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Zomg::hit(int damage) {
    MySound popSound("MOABBloon");
    popSound.start();

    health -= damage;
    health -= debuff.bonusDamage; // Apply bonus damage from debuffs

    if (health <= 0) {
        MySound destroyingSound("DestroyingMOABBloon");
        destroyingSound.start();
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
    flog << tag << " reached the end of the track!" << std::endl;
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

    DrawTexturePro(Game::Instance().getTextureManager().getTexture(tag), 
                   {0, 0, size.x, size.y},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   WHITE); // Draw the Zomg bloon texture with the specified position and rotation
}

Rectangle Zomg::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Zomg::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void Zomg::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}
    
void Zomg::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the Zomg bloon
    return;
}

void Zomg::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a MOAB class 
    debuff += moabDebuff; 
}

void Zomg::setModifies(const EnemyModifies& modifies) {
    // Set the enemy modifiers for the Zomg bloon
    speed = static_cast<int>(speed * modifies.speed);
    health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Zomg::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Zomg bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}