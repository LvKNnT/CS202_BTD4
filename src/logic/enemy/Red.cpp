#include "Red.h"
#include <fstream>

Red::Red(Vector2 position)
    : Enemy(position, {0, 0}, 0.0f, BloonType::Red, 1, 100, 1, 1) { 
    /**
     * Health = 1
     * Speed = 100
     * Reward = 1
     * Live lost = 1
     *  */ 

    // Load the texture for the Red bloon
    Game::Instance().getTextureManager().loadTexture("Red", "../assets/enemy/Normal Bloons/default/BTD6Red.png");
    texture = Game::Instance().getTextureManager().getTexture("Red"); 
    
    // Change the size of the bloon based on the texture size
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);

    // Set tag
    tag = "RedBloon";
}
Red::~Red() {
    // Cleanup if necessary
}

bool Red::hit(int damage) {
    health -= damage;
    if (health <= 0) {
        // Logic for when the Red bloon is popped
        // For example, you might want to remove it from the game or trigger an event
        std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
        flog << "Red bloon popped!" << std::endl;
        flog.close();

        return true;
    }

    return false;
}

void Red::die() {
    // Logic for when the Red bloon reaches the end of the track
    // For example, you might want to handle lives lost or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Red bloon reached the end of the track!" << std::endl;
    flog.close();
}

void Red::draw() const {
    // Draw the Red bloon using raylib functions
    // For example, you might use DrawCircle or DrawTexture depending on your implementation
    DrawCircleV(position, 10, BLUE); // Example drawing a red circle for the bloon

    DrawTexturePro(texture, 
        {0, 0, size.x, size.y}, 
        {position.x, position.y, size.x, size.y}, 
        {size.x / 2, size.y / 2}, 
        rotation, 
        WHITE); // Draw the bloon texture at the specified position
}

std::unique_ptr<Enemy> Red::clone() const {
    // Create a new instance of Red bloon with the same properties
    return std::make_unique<Red>(*this);
}

Rectangle Red::getBoundingBox(float& x, float& y, float& width, float& height) const {
    // Provide the bounding box for collision detection
    return {position.x - size.x / 2, position.y - size.y / 2, size.x, size.y};
}

bool Red::isActive() const {
    // Check if the Red bloon is still active (not popped)
    return health > 0;
}

void Red::setActive(bool active) {
    // Set the active state of the Red bloon
    isActiveFlag = active;
    if (!active) {
        health = 0; // If not active, consider it popped
    }
}