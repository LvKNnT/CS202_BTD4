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

    tag = fullTag;

    // Update size based on the loaded texture
    size.x = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).width);
    size.y = static_cast<float>(Game::Instance().getTextureManager().getTexture(tag).height);
}

bool White::hit(int damage) {
    if(!std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->isAudioPlaying(AudioType::SFXSound, "BombExplosion")) {
        MySound popSound("NormalBloon");
        popSound.start();
    }
    health -= damage;
    health -= debuff.bonusOnHitDamage; // Apply bonus damage from debuffs

    if (health <= 0) {
        drawDeadEffect();
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

    DrawTextureV(Game::Instance().getTextureManager().getTexture(tag), draw_position, effects.colorTint); // Draw the bloon texture at its position
    drawEffect();
}

Rectangle White::getBoundingBox() const {
    return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

bool White::isActive() const {
    // Check if the bloon is still active (not popped)
    return isActiveFlag;
}

void White::setActive(bool active) {
    // Set the active state of the White bloon
    isActiveFlag = active;
}

void White::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void White::setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) {
    // Since it is a normal bloon
    debuff += normalDebuff; 
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