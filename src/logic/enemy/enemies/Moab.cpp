#include "Moab.h"
#include <fstream>

Moab::Moab(Vector2 position) 
    : Enemy(position, {0, 0}, 0.0f, BloonType::Moab, 200, 100, 1, 616) {
    /**
     * Health = 200
     * Speed = 100
     * Reward = 1
     * Lives lost = 616
     */

    // Variable initialization that cant use initializer list
    tag = "MOAB";
}
Moab::~Moab() {
    // Cleanup if necessary
}

std::unique_ptr<Enemy> Moab::clone() const {
    return std::make_unique<Moab>(*this);
}

void Moab::loadTexture() {
    // Load the texture
    std::string fullTag = properties.getFullTag(tag);
    std::string path = "../assets/enemy/MOAB Class Bloons/" + fullTag + ".png";
    Game::Instance().getTextureManager().loadTexture(fullTag, path);

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Moab::hit(int damage) {
    MySound popSound("MOABBloon");
    popSound.start();
    health -= damage;

    if (health <= 0) {
        MySound destroyingSound("DestroyingMOABBloon");
        destroyingSound.start();
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Moab bloon popped!" << std::endl;
        flog.close();
        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();
    
    return true;
}

void Moab::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Moab::draw() const {
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
                   WHITE); // Draw the Moab bloon texture with the specified position and rotation
}

Rectangle Moab::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Moab::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Moab::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}
    
void Moab::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation angle for the Moab bloon
    return;
}

void Moab::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a MOAB class bloon
    debuff += moabDebuff; 
}

void Moab::setModifies(const EnemyModifies& modifies) {
    // Set the enemy modifiers for the Moab bloon
    speed = static_cast<int>(speed * modifies.speed);
    health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}

void Moab::setProperties(const BloonProperties& properties) {
    // Set the bloon properties for the Moab bloon
    this->properties = properties;
    
    if(properties.isFortified) {
        health *= 2; // Fortified bloons have double health
    }
}