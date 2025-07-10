#include "Dart.h"

#include <fstream>

Dart::Dart(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan)
    : Bullet(position, size, rotation, BulletType::Dart, damage, speed, pierce, lifeSpan) {
    tag = "Dart";
}

std::unique_ptr<Bullet> Dart::clone() const {
    return std::make_unique<Dart>(*this);
}

void Dart::loadTexture() {
    // Load the texture for the Dart bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Dart.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

bool Dart::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void Dart::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the dart

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
                   WHITE); // Draw the Dart texture with the specified position and rotation
}

void Dart::die() {
    // Logic for when the Dart bullet reaches the end of its life
    // For example, you might want to remove it from the game or trigger an event
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Dart bullet reached the end of its life!" << std::endl;
    flog.close();
}

Rectangle Dart::getBoundingBox() const {
    return {
        position.x - size.x / 2.0f,
        position.y - size.y / 2.0f,
        size.x,
        size.y
    }; 
}

bool Dart::isActive() const {
    // Logic to determine if the Dart bullet is still active
    // For example, you might check if it has reached its target or if it has been destroyed
    return true; // Assuming the dart is always active for this example
}

void Dart::setActive(bool active) {
    // Logic to set the active state of the Dart bullet
    // For example, you might want to deactivate it when it hits a target or reaches its end
    std::fstream flog("../logs/log.txt", std::ios::out | std::ios::app);
    flog << "Dart bullet active state set to: " << (active ? "true" : "false") << std::endl;
    flog.close();
}

void Dart::setRotation(float rotation) {
    // Set the rotation of the Dart bullet
    this->rotation = rotation; // Assuming rotation is in degrees
    // Additional logic for handling rotation can be added here if needed
}

