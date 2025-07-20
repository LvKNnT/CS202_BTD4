#include "Yellow.h"
#include <fstream>

Yellow::Yellow(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Yellow, 1, 320, 1, 4) {
    /**
     * Health = 1
     * Speed = 320
     * Reward = 1
     * Lives lost = 4
     */

    // Variable initialization that can't use initializer list
    tag = "YellowBloon";
}  

std::unique_ptr<Enemy> Yellow::clone() const {
    return std::make_unique<Yellow>(*this);
}

void Yellow::loadTexture() {
    // Load the texture
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/enemy/Normal Bloons/default/BTD6Yellow.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);

    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

bool Yellow::hit(int damage) {
    health -= damage;

    if (health <= 0) {
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Yellow bloon popped!" << std::endl;
        flog.close();

        return false;
    }

    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Enemy " << tag << " is still alive with health: " << health << std::endl;
    flog.close();

    return true;
}

void Yellow::die() {
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << tag << " reached the end of the track!" << std::endl;
    flog.close();
}

void Yellow::draw() const {
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

Rectangle Yellow::getBoundingBox() const {
    return Rectangle{
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    };
}

bool Yellow::isActive() const {
    // Check if the bloon is still active (not popped)
    return health > 0;
}

void Yellow::setActive(bool active) {
    // Set the active state of the Yellow bloon
    isActiveFlag = active;
}

void Yellow::setRotation(float rotation) {
    return; // Normal bloon does not need rotation
}

void Yellow::setModifies(const EnemyModifies& modifies) {
    // Set the modifications for the normal bloon
    speed = static_cast<int>(speed * modifies.speed);
    // health = static_cast<int>(health * modifies.health);
    reward = static_cast<int>(reward * modifies.reward);
}