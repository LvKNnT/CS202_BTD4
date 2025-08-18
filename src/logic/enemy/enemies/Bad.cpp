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

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool Bad::hit(int damage) {
    health -= damage;
    health -= debuff.bonusOnHitDamage; // Apply bonus damage from debuffs

    if (health <= 0) {
        drawDeadEffect();
        if(!std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->isAudioPlaying(AudioType::SFXSound, "BombExplosion")) {
            MySound popSound("MOABBloon");
            popSound.start();
        }
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

    DrawTexturePro(Game::Instance().getTextureManager().getTexture(tag), 
                   {0, 0, size.x, size.y},
                   {draw_position.x, draw_position.y, size.x, size.y},
                   {size.x / 2.0f, size.y / 2.0f},
                   rotation,
                   effects.colorTint); // Draw the Bad bloon texture with the specified position and rotation
    drawEffect();
}

Rectangle Bad::getBoundingBox() const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool Bad::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void Bad::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
}
    
void Bad::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a MOAB class
    debuff += moabDebuff;
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