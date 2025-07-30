#include "ArrowCrit.h"
#include "../../../core/Game.h"

ArrowCrit::ArrowCrit()
    : Bullet(BulletType::ArrowCrit) {
    tag = "ArrowCrit";
}

std::unique_ptr<Bullet> ArrowCrit::clone() const {
    return std::make_unique<ArrowCrit>(*this);
}

void ArrowCrit::loadTexture() {
    // Load the texture for the Arrow Crit bullet
    Game::Instance().getTextureManager().loadTexture(tag, "../assets/bullet/Arrow_0.png");
    texture = Game::Instance().getTextureManager().getTexture(tag);
    
    // Update size based on the loaded texture
    size.x = static_cast<float>(texture.width);
    size.y = static_cast<float>(texture.height);
}

void ArrowCrit::init(Vector2 position, Vector2 size, float rotation, int damage, int speed, int pierce, float lifeSpan, BulletProperties properties, AttackBuff attackBuff, int towerId) {
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->damage = damage;
    this->speed = speed;
    this->pierce = pierce;
    this->lifeSpan = lifeSpan;
    this->properties = properties; 
    this->attackBuff = attackBuff; 
    this->towerId = towerId; 
}

bool ArrowCrit::hit(int damage) {
    pierce -= damage;
    
    return pierce <= 0; // Indicating that the hit was successful
}

void ArrowCrit::draw() const {
    // Check if the bullet is active before drawing
    if(!isActiveFlag) {
        return; 
    }

    DrawCircleV(position, 10, RED); // Example drawing a red circle for the arrow crit

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
                   WHITE); // Draw the Arrow Crit texture with the specified position and rotation
}

int ArrowCrit::die() {
    // Handle the death of the Arrow Crit bullet
    isActiveFlag = false; // Mark the bullet as inactive
    return 0; // Return 0 to indicate successful death handling
}

std::vector<std::unique_ptr<Bullet>> ArrowCrit::getChild() {
    // Arrow Crit bullet does not spawn any child bullets, so return an empty vector
    return {};
}

Rectangle ArrowCrit::getBoundingBox() const {
    return { position.x, position.y, size.x, size.y }; // Return the bounding box of the bullet
}

bool ArrowCrit::isActive() const {
    return isActiveFlag; // Return the active status of the bullet
}   

void ArrowCrit::setActive(bool active) {
    isActiveFlag = active; // Set the active status of the bullet
}

void ArrowCrit::setRotation(float rotation) {
    this->rotation = rotation; // Set the rotation of the bullet
}